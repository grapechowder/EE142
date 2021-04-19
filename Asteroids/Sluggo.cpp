// Sluggo is the larger alien spaceship. He has two different states to be in -- attacking or retreating.
// When attacking, he moves in a random fashion, and fires a bullet every once in a while. He does not aim
// his bullets -- just fires in a random direction. After a while, he goes to retreat mode, where he moves
// off the left side of the screen. He then disappears.
//
// To get the random motion, we pick a velocity in a random direction, and then set a timer to go off
// to change the direction. We also use timers to decide when to change state.

#include <cmath>

#include <Thing.hpp>
#include <MovingThing.hpp>
#include <Vector2d.hpp>
#include <Timer.hpp>
#include <VertexShape.hpp>

#include "Sluggo.h"
#include "Wall.h"
#include "Bullet.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "Asteroid.h"
#include "Particle.h"

using namespace vmi;

Sluggo::Sluggo() : MovingThing(Vector2d(-40, 50), Vector2d(100, 0), Vector2d(), new VertexShape()),
				   retreating(false),
				   retreatVelocity(Vector2d(-100, 0)) // retreat to the left
{
	// build the shape first
	VertexShape *vs = dynamic_cast<VertexShape *>(shape);
	vs->moveTo(Vector2d(-24, 4));
	vs->lineTo(Vector2d(-8, -4));
	vs->lineTo(Vector2d(-5, -13));
	vs->lineTo(Vector2d(5, -13));
	vs->lineTo(Vector2d(8, -4));
	vs->lineTo(Vector2d(24, 4));
	vs->lineTo(Vector2d(12, 13));
	vs->lineTo(Vector2d(-12, 13));
	vs->lineTo(Vector2d(-24, 4));
	vs->moveTo(Vector2d(-8, -4));
	vs->lineTo(Vector2d(8, -4));

	// create timer to shoot after 2-5 seconds
	int time = rand() % 3 + 2;
	shootTimer = Timer::createTimer(time, [&]() {
		shoot();
	});

	// create timer to turn after 3-8 seconds
	time = rand() % 5 + 3;
	turnTimer = Timer::createTimer(time, [&]() {
		turn();
	});

	// and timer to retreat after 15-20 seconds
	time = rand() % 5 + 15;
	retreatTimer = Timer::createTimer(time, [&]() {
		retreat();
	});
}

Sluggo::~Sluggo()
{
	// cancel all the timers
	if (shootTimer != nullptr)
		shootTimer->cancel();
	if (turnTimer != nullptr)
		turnTimer->cancel();
	if (retreatTimer != nullptr)
		retreatTimer->cancel();

	delete shape;
}

void Sluggo::handleCollision(const Thing *other)
{
	// is this a wall?
	if (typeid(*other) == typeid(Wall))
	{
		// are we retreating or attacking?
		if (retreating)
		{
			// we go away when we hit the wall to hide
			die();
		}
		else
		{
			// wraparound our location
			const Wall *wall = dynamic_cast<const Wall *>(other);

			// add offset vector from wall
			x += wall->getOffset();
		}
	}

	// anything else hit is fatal
	else if ((typeid(*other) == typeid(Player)) || (typeid(*other) == typeid(Asteroid)) || (typeid(*other) == typeid(Bullet)) || (typeid(*other) == typeid(PlayerBullet)))
	{
		die();
	}
}

// Explode when we die
void Sluggo::die()
{
	Particle::explode(this);

	Thing::die();
}

// Sluggo is worth 200 points
int Sluggo::getPoints() const
{
	return 200;
}

// Shoot in a random direction, and then reload to shoot again in 2-5 seconds
void Sluggo::shoot()
{
	const double pi = 3.1415926;
	double ang = (rand() % 360) * (pi / 180.0); // random direction

	Vector2d dir(sin(ang), -cos(ang));

	// shoot the bullet
	new Bullet(x + 40 * dir, dir);

	// re-load the timer to shoot again
	int time = rand() % 3 + 2; // 2 - 5 seconds
	shootTimer = Timer::createTimer(time, [&]() {
		shoot();
	});
}

// Turn in a random direction
void Sluggo::turn()
{
	const double pi = 3.1415926;
	double ang = (rand() % 360) * (pi / 180.0);

	v = 100 * Vector2d(sin(ang), -cos(ang));

	// re-load the timer to turn again
	int time = rand() % 5 + 5; // 5 - 10 seconds
	turnTimer = Timer::createTimer(time, [&]() {
		turn();
	});
}

// Retreat -- move offscreen until we hit a wall
void Sluggo::retreat()
{
	retreating = true;

	// move offscreen
	v = retreatVelocity;

	// cancel any pending turns
	if (turnTimer)
	{
		turnTimer->cancel();
		turnTimer = nullptr;
	}

	// and we only retreat once
	retreatTimer = nullptr;
}
