// Class to represent an asteroid. The shape is created as an octagon, with some randomness added to
// each vertex, to make an odd shape. We also use the scale factor to have three different
// sizes, large (scale = 4.0), medium (scale = 2.0) and small (scale = 1.0). When an
// asteroid is destroyed, it splits into two smaller asteroids.

#include <cmath>
#include <cstdlib>
#include <MovingThing.hpp>
#include <Thing.hpp>
#include <Vector2d.hpp>
#include <VertexShape.hpp>

#include "Asteroid.h"
#include "Wall.h"
#include "Player.h"
#include "Bullet.h"
#include "PlayerBullet.h"
#include "Sluggo.h"
#include "Particle.h"

using namespace vmi;

int Asteroid::count = 0;

Asteroid::Asteroid(Vector2d position) : MovingThing(position,
													Vector2d(),
													Vector2d(),
													new VertexShape())
{
	const double pi = 3.1415926;

	// build the shape
	VertexShape *vs = dynamic_cast<VertexShape *>(shape);
	vs->moveTo(Vector2d(0, -10));

	for (int i = 1; i < 8; i++)
	{
		// angle = 2pi/8 + some randomness
		double ang = i * pi / 4.0 + (rand() % 1000) / 1000.0 * pi / 8;

		// pick a point on that angle between 5 and 10
		double radius = rand() % 5 + 5.0;

		// for odd vertices, make them a little bigger
		if (i & 1)
		{
			radius += 5.0;
		}

		// convert to an x,y location
		vs->lineTo(radius * Vector2d(sin(ang), -cos(ang)));
	}

	vs->lineTo(Vector2d(0, -10));

	// pick a random rotation angle
	angle = rand() % 360;

	// and a random velocity in that direction
	double speed = rand() % 150 + 50.0; // between 50 and 200
	v = speed * Vector2d(sin(angle * pi / 180.0), -cos(angle * pi / 180.0));

	// make it a big asteroid
	scale = 4.0;

	// and add to our total
	count++;
}

// Copy constructor -- we're abusing C++ here. Our copy constructor makes a copy of the
// asteroid, but reduces the size by changing the scale factor.
Asteroid::Asteroid(const Asteroid &other) : MovingThing(other)
{
	// we need to copy the shape of the asteroid
	shape = new VertexShape(*(dynamic_cast<VertexShape *>(other.shape)));

	// scale it down
	scale *= 0.5;

	// change location and velocity slightly
	x += Vector2d(rand() % 20 - 10, rand() % 20 - 10);
	v += Vector2d(rand() % 100 - 50, rand() % 100 - 50);

	// add it to the count
	count++;
}

// Destructor -- delete the shape and subtract from the count
Asteroid::~Asteroid()
{
	delete shape;

	count--;
}

// When asteroid is destroyed, it splits into 2 smaller asteroids.
void Asteroid::splitAndDie()
{
	if (scale > 1.0)
	{
		// we're large or medium, so split into 2 children
		new Asteroid(*this);
		new Asteroid(*this);
	}

	// that blowed up real good!
	Particle::explode(this);

	// now die for real
	die();
}

// If we hit the wall, change position. If we hit the player, an alien, or a bullet, we die. But, ignore
// any collisions with other asteroids
void Asteroid::handleCollision(const Thing *other)
{
	// if we hit a wall, then wraparound to new location
	if (typeid(*other) == typeid(Wall))
	{
		const Wall *wall = dynamic_cast<const Wall *>(other);

		// check if center of asteroid has actually entered wall's box (ignore collision if not)
		if (wall->getBounds().contains(x + center))
		{
			// add offset vector from wall
			x += wall->getOffset();
		}
	}

	// if we hit an alien or bullet, then die
	else if ((typeid(*other) == typeid(PlayerBullet)) || (typeid(*other) == typeid(Bullet)) || (typeid(*other) == typeid(Sluggo)))
	{
		splitAndDie();
	}

	// if we hit the player, we also
	else if (typeid(*other) == typeid(Player))
	{
		splitAndDie();
	}
}

// Return number of asteroids currently alive
int Asteroid::getCount()
{
	return count;
}

// Return the number of points for hitting this asteroid -- large are worth 20, medium 50, and small 100
int Asteroid::getPoints() const
{
	if (scale >= 4.0)
		return 20;
	else if (scale >= 2.0)
		return 50;
	else
		return 100;
}
