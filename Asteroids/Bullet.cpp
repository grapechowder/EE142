// Class to represent the bullet. Bullet is drawn as a small rectangle, and bullets have a
// limited lifespan.

#include <cmath>
#include <Thing.hpp>
#include <MovingThing.hpp>
#include <Vector2d.hpp>
#include <VertexShape.hpp>
#include <Timer.hpp>
#include <Color.hpp>

#include "Wall.h"
#include "Player.h"
#include "Bullet.h"

using namespace vmi;

Bullet::Bullet(Vector2d position, Vector2d dir)
	: MovingThing(position, 450 * dir, Vector2d(), new VertexShape())
{
	// create the shape as a short line
	VertexShape *vs = dynamic_cast<VertexShape *>(shape);
	vs->moveTo(Vector2d(0, 8), Color::Red);
	vs->lineTo(Vector2d(0, -8), Color::Red);

	// set angle of rotation
	angle = atan2(dir.getX(), -dir.getY()) * 180.0 / 3.1415926;

	// create a timer to kill this bullet
	timer = Timer::createTimer(1.0, [&]() {
		die();
		timer = nullptr; // so we don't try to cancel it
	});
}

Bullet::~Bullet()
{
	// if timer is still active, then cancel it
	if (timer != nullptr)
	{
		timer->cancel();
	}

	// delete the shape
	delete shape;
}

// Bullet dies if it hits anything except a wall
void Bullet::handleCollision(const Thing *other)
{
	// if we hit a wall, then wraparound to new location
	if (typeid(*other) == typeid(Wall))
	{
		const Wall *wall = dynamic_cast<const Wall *>(other);

		// add offset vector from wall
		x += wall->getOffset();
	}

	// die if we hit anything else
	else
	{
		die();
	}
}
