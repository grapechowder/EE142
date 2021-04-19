// Base class for representing all objects in our game
#pragma once
#ifndef VMI_GAME_THING_H
#define VMI_GAME_THING_H


#include <set>
#include "Graphics.hpp"

#include "Vector2d.hpp"
#include "BoundingBox.hpp"
#include "Shape.hpp"

namespace vmi {

#ifndef ZYBOOKS
class Thing
{
public:
	Thing() : x(Vector2d()), angle(0.0), center(Vector2d()),
        scale(1.0), shape(nullptr), alive(true), z(0.0) {
        things.insert(this);
    }

	Thing(const Vector2d _x, Shape* _shape, double _z = 0.0)
        : x(_x), angle(0.0), center(Vector2d()),
        scale(1.0), shape(_shape), alive(true), z(_z) {
	    // add to list of all things
	    things.insert(this);
    }

    Thing(const Thing& other)
        : x(other.x), angle(other.angle), center(other.center),
        scale(other.scale), shape(other.shape), alive(true), z(other.z) {
        // add to list of all things
        things.insert(this);
    }

    Thing& operator=(const Thing& rtSide);
	virtual ~Thing() { /* don't remove from list, that's done in removeDeadThings*/ }

	// draw the thing
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// get a bounding box around thing
	virtual const BoundingBox getBounds() const;

	// is this thing colliding with another thing?
    bool isCollidingWith(const Thing* other) const {
    	return alive && other->alive && getBounds().intersects(other->getBounds());
    }

	// handle a collision with another thing
	virtual void handleCollision(const Thing* other) = 0;

    // is this thing still alive?
    bool isAlive() const { return alive; }

    // Kill this thing
    virtual void die() { alive = false; }

    // get this thing's position, rotation, scale, center position, shape
    const Vector2d getPosition() const { return x; }
    const Vector2d getCenter() const { return center; }
    double getRotation() const { return angle; }
    double getScale() const { return scale; }
    const Shape* getShape() const { return shape; }


    // set the z-order for this thing
    void setZ(double _z) { z = _z; }

protected:
	Vector2d x;			// position of thing
    double angle;       // rotation angle
    Vector2d center;    // center point, used for rotation
    double scale;       // scaling factor
	Shape *shape;		// shape for drawing

    bool alive;         // whether or not this thing is still alive

private:
    double z;           // z-ordering, 0 = foregraound, >0 = background

	// The following are static functions that operate on all Things
public:
	static void drawAll(sf::RenderWindow& window);		// draw everyone
	static void handleCollisions();                     // check for anyone colliding with anyone else
    static void removeDeadThings();                     // remove all the dead things from list
    static void killAllThings();                        // remove all things from game

	// Static list of all Things
private:

    // Functor used to sort things based on z-order
    struct cmpThings
    {
        bool operator()(const Thing* a, const Thing* b) const
        {
            return a->z > b->z;
        }
    };
	static inline std::multiset<Thing*, cmpThings> things;
};


inline Thing& Thing::operator=(const Thing& rtSide)
{
    // is this me?
    if (this != &rtSide) {
        // delete me from list of all things so list stays sorted
        things.erase(this);

        // delete my old shape
        if (shape) delete shape;

        // copy everything
        x = rtSide.x;
        angle = rtSide.angle;
        center = rtSide.center;
        scale = rtSide.scale;
        z = rtSide.z;
        shape = nullptr;        // can't copy this -- needs to be done in child class
        alive = true;

        // add back to list of all things
        things.insert(this);
    }

    return *this;
}

// draw the thing -- we have to apply rotation, scale, and translation
inline void Thing::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // get center of rotation
    Vector2d cntr = x + center;

    // scale it, rotate, and translate
    states.transform.scale((float) scale, (float)scale, (float) cntr.getX(), (float) cntr.getY());
    states.transform.rotate((float) angle, (float)cntr.getX(), (float)cntr.getY());
    states.transform.translate((float) x.getX(), (float) x.getY());

    // now draw it
	shape->draw(target, states);
}

// get a bounding box around thing -- we have to take the rotation, scale, and position into account,
// so we use SFML's transforms for this
inline const BoundingBox Thing::getBounds() const
{
    // get shape's bounding box
    BoundingBox bb = shape->getBounds();

    // convert to SFML's box
    sf::FloatRect sf_bb((float)bb.getUl().getX(), (float) bb.getUl().getY(),
                        (float)bb.getWidth(), (float)bb.getHeight());

    // get center of rotation
    Vector2d cntr = x + center;

    // build a transform
    sf::Transform t;
    t.scale((float)scale, (float)scale, (float)cntr.getX(), (float)cntr.getY());
    t.rotate((float) angle, (float)cntr.getX(), (float)cntr.getY());
    t.translate((float)x.getX(), (float)x.getY());

    // transform the bounding box
    sf_bb = t.transformRect(sf_bb);

    // convert it back to our bounding box
    return BoundingBox(Vector2d(sf_bb.left, sf_bb.top), sf_bb.width, sf_bb.height);
}



/********************************************************************************************/
/* The following functions operate on the list of all things.                               */
/********************************************************************************************/
// Draw all things
inline void Thing::drawAll(sf::RenderWindow& window)
{
	// clear the window
	window.clear();

	// draw everyone
	for (auto it = things.begin(); it != things.end(); ++it) {
		(*it)->draw(window, sf::RenderStates::Default);
	}

	// now display the updated window
	window.display();
}

// Handle any collisions between things
inline void Thing::handleCollisions()
{
    // repeat for all things
	for (auto it = things.begin(); it != things.end(); ++it) {
		// compare to all other things
        for (auto jt = std::next(it); jt != things.end(); ++jt) {
			// are we colliding?
			if ((*it)->isCollidingWith(*jt)) {
				// handle the collision
				(*it)->handleCollision(*jt);
				(*jt)->handleCollision(*it);
			}
		}
	}
}

// Bring out your dead!
// Go through list and remove any things that aren't alive anymore. Only tricky part
// of this is making sure we don't invalidate our iterator as we go through the list.
inline void Thing::removeDeadThings()
{
    auto it = things.begin();

    while (it != things.end()) {
        Thing *thing = *it;     // get the thing itself

        // is this thing dead?
        if (!thing->alive) {
            // dead, so remove it from the list of all things
            it = things.erase(it);

            // and delete him
            delete thing;
        }
        else {
            // still alive, so go on to next thing
            ++it;
        }
    }
}

// Kill all things -- we can use this to end a level by removing all Things from the game
inline void Thing::killAllThings()
{
    for (auto it = things.begin(); it != things.end(); ++it) {
		(*it)->alive = false;;
    }
}

#else
class Thing
{
public:
	Thing() : x(Vector2d()), angle(0.0), center(Vector2d()),
        scale(1.0), shape(nullptr), alive(true), z(0.0) {

    }

	Thing(const Vector2d _x, Shape* _shape, double _z = 0.0)
        : x(_x), angle(0.0), center(Vector2d()),
        scale(1.0), shape(_shape), alive(true), z(_z) {
    }

    Thing(const Thing& other)
        : x(other.x), angle(other.angle), center(other.center),
        scale(other.scale), shape(other.shape), alive(true), z(other.z) {
    }

    Thing& operator=(const Thing& rtSide);
	virtual ~Thing() { /* don't remove from list, that's done in removeDeadThings*/ }

	// draw the thing
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// get a bounding box around thing
	virtual const BoundingBox getBounds() const;

	// is this thing colliding with another thing?
    bool isCollidingWith(const Thing* other) const {
    	return alive && other->alive && getBounds().intersects(other->getBounds());
    }

	// handle a collision with another thing
	virtual void handleCollision(const Thing* other) = 0;

    // is this thing still alive?
    bool isAlive() const { return alive; }

    // Kill this thing
    virtual void die() { alive = false; }

    // get this thing's position, rotation, scale, center position, shape
    const Vector2d getPosition() const { return x; }
    const Vector2d getCenter() const { return center; }
    double getRotation() const { return angle; }
    double getScale() const { return scale; }
    const Shape* getShape() const { return shape; }


    // set the z-order for this thing
    void setZ(double _z) { z = _z; }

protected:
	Vector2d x;			// position of thing
    double angle;       // rotation angle
    Vector2d center;    // center point, used for rotation
    double scale;       // scaling factor
	Shape *shape;		// shape for drawing

    bool alive;         // whether or not this thing is still alive

private:
    double z;           // z-ordering, 0 = foregraound, >0 = background

	// The following are static functions that operate on all Things
public:
	static void drawAll(sf::RenderWindow& window);		// draw everyone
	static void handleCollisions();                     // check for anyone colliding with anyone else
    static void removeDeadThings();                     // remove all the dead things from list
    static void killAllThings();                        // remove all things from game

	// Static list of all Things
private:

	
};


inline Thing& Thing::operator=(const Thing& rtSide)
{
    // is this me?


    return *this;
}

// draw the thing -- we have to apply rotation, scale, and translation
inline void Thing::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
 
}

// get a bounding box around thing -- we have to take the rotation, scale, and position into account,
// so we use SFML's transforms for this
inline const BoundingBox Thing::getBounds() const
{
    // get shape's bounding box
    BoundingBox bb = shape->getBounds();

    // convert to SFML's box
    sf::FloatRect sf_bb((float)bb.getUl().getX(), (float) bb.getUl().getY(),
                        (float)bb.getWidth(), (float)bb.getHeight());

    // get center of rotation
    Vector2d cntr = x + center;

    // build a transform
    sf::Transform t;
    t.scale((float)scale, (float)scale, (float)cntr.getX(), (float)cntr.getY());
    t.rotate((float) angle, (float)cntr.getX(), (float)cntr.getY());
    t.translate((float)x.getX(), (float)x.getY());

    // transform the bounding box
    sf_bb = t.transformRect(sf_bb);

    // convert it back to our bounding box
    return BoundingBox(Vector2d(sf_bb.left, sf_bb.top), sf_bb.width, sf_bb.height);
}



/********************************************************************************************/
/* The following functions operate on the list of all things.                               */
/********************************************************************************************/
// Draw all things
inline void Thing::drawAll(sf::RenderWindow& window)
{

}

// Handle any collisions between things
inline void Thing::handleCollisions()
{
 
}

// Bring out your dead!
// Go through list and remove any things that aren't alive anymore. Only tricky part
// of this is making sure we don't invalidate our iterator as we go through the list.
inline void Thing::removeDeadThings()
{
 
}

// Kill all things -- we can use this to end a level by removing all Things from the game
inline void Thing::killAllThings()
{

}

#endif

} // namespace vmi

#endif