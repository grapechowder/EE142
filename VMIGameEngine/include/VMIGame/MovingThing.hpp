// Class to represent things that can move
#pragma once
#ifndef VMI_GAME_MOVING_THING_H
#define VMI_GAME_MOVING_THING_H


#include <set>
#include "Graphics.hpp"

#include "Vector2d.hpp"
#include "Shape.hpp"
#include "Thing.hpp"

namespace vmi {

#ifndef ZYBOOKS
class MovingThing : public Thing
{
public:
	MovingThing() : Thing() { movingThings.insert(this); }

	MovingThing(const Vector2d _x, const Vector2d _v, const Vector2d _a, Shape* _shape, double _z = 0)
		: Thing(_x, _shape, _z), v(_v), a(_a), w(0.0) {
		// add to list of moving things
		movingThings.insert(this);
	}

    MovingThing(const MovingThing& other) 
		: Thing(other), v(other.v), a(other.a), w(other.w) {
    	// add to list of moving thigs
   		movingThings.insert(this);
	}

    MovingThing& operator=(const MovingThing& rtSide);

	virtual ~MovingThing() { movingThings.erase(this); }

		// move ahead in time
	virtual void move(double dt) {
		// update position, velocity, rotation
		x += v*dt + (0.5*dt*dt)*a;
		v += a*dt;
	    angle += w*dt;
	}
    
    // getter functions
    const Vector2d getVelocity() const { return v; }
    const Vector2d getAcceleration() const { return a; }

protected:
	Vector2d v;			// velocity
	Vector2d a;			// acceleration
    double w;           // angular velocity

	// Static functions to move everyone
public:
	static void moveAll(double dt) {
		for (auto it = movingThings.begin(); it != movingThings.end(); ++it) {
			(*it)->move(dt);
		}
	}


	// Static list of all moving things
private:
	static inline std::set<MovingThing*> movingThings;
};


// Assignment operator
inline MovingThing& MovingThing::operator=(const MovingThing& rtSide)
{
    // is this me?
    if (this != &rtSide) {
        Thing::operator=(rtSide);
        
        v = rtSide.v;
        a = rtSide.a;
        w = rtSide.w;
        
        // don't add to list of moving things -- should already be there
    }
    
    return *this;
}

#else
class MovingThing : public Thing
{
public:
	MovingThing() : Thing() { }

	MovingThing(const Vector2d _x, const Vector2d _v, const Vector2d _a, Shape* _shape, double _z = 0)
		: Thing(_x, _shape, _z), v(_v), a(_a), w(0.0) {
		
	}

    MovingThing(const MovingThing& other) 
		: Thing(other), v(other.v), a(other.a), w(other.w) {
	}

    MovingThing& operator=(const MovingThing& rtSide);

	virtual ~MovingThing() {  }

		// move ahead in time
	virtual void move(double dt) {
		// update position, velocity, rotation
		x += v*dt + (0.5*dt*dt)*a;
		v += a*dt;
	    angle += w*dt;
	}
    
    // getter functions
    const Vector2d getVelocity() const { return v; }
    const Vector2d getAcceleration() const { return a; }

protected:
	Vector2d v;			// velocity
	Vector2d a;			// acceleration
    double w;           // angular velocity

	// Static functions to move everyone
public:
	static void moveAll(double dt) {

	}


};


// Assignment operator
inline MovingThing& MovingThing::operator=(const MovingThing& rtSide)
{
    // is this me?
    if (this != &rtSide) {
        Thing::operator=(rtSide);
        
        v = rtSide.v;
        a = rtSide.a;
        w = rtSide.w;
        
        // don't add to list of moving things -- should already be there
    }
    
    return *this;
}

#endif

} // namespace vmi

#endif