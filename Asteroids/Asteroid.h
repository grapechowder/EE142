// Class to represent an asteroid. The shape is created as an octagon, with some randomness added to
// each vertex, to make an odd shape. We also use the scale factor to have three different
// sizes, large (scale = 4.0), medium (scale = 2.0) and small (scale = 1.0). When an
// asteroid is destroyed, it splits into two smaller asteroids.

#pragma once

#include <Thing.hpp>
#include <MovingThing.hpp>
#include <Vector2d.hpp>

class Asteroid : public vmi::MovingThing
{
public:
	Asteroid(vmi::Vector2d position);
	Asteroid(const Asteroid &other);
	~Asteroid();

	void handleCollision(const vmi::Thing *other);

	int getPoints() const; // points for hitting this asteroid

public:
	static int getCount();

private:
	void splitAndDie(); // split into 2 asteroids when destroyed
	static int count;	// total number of asteroids that are alive
};
