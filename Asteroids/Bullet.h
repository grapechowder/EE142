// Class to represent the bullet. Bullet is drawn as a small rectangle, and bullets have a
// limited lifespan.

#pragma once

#include <MovingThing.hpp>
#include <Thing.hpp>
#include <Vector2d.hpp>
#include <Timer.hpp>

class Bullet : public vmi::MovingThing
{
public:
	Bullet(vmi::Vector2d position, vmi::Vector2d dir);
	~Bullet();

	void handleCollision(const vmi::Thing *other);

protected:
	vmi::Timer *timer;
};
