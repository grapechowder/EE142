// Mr. Bill is the smaller alien spaceship. He has two different states to be in -- attacking or retreating.
// When attacking, he moves in a random fashion, and fires a bullet every once in a while. He aims
// his bullets toward the player's ship. After a while, he goes to retreat mode, where he moves
// off the right side of the screen. He then disappears.
//
// To get the random motion, we pick a velocity in a random direction, and then set a timer to go off
// to change the direction. We also use timers to decide when to change state.

#include <cmath>

#include <Thing.hpp>
#include <MovingThing.hpp>
#include <Vector2d.hpp>
#include <Timer.hpp>
#include <VertexShape.hpp>

#include "MrBill.h"
#include "Wall.h"
#include "Bullet.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "Asteroid.h"
#include "Particle.h"

using namespace vmi;

MrBill::MrBill(const Player *_player) : MovingThing(Vector2d(840, 100), Vector2d(-100, 0), Vector2d(), new VertexShape()),
										retreating(false),
										retreatVelocity(Vector2d(100, 0)), // retreat to the right
										player(_player)
{
	// build the shape first
	VertexShape *vs = dynamic_cast<VertexShape *>(shape);
	vs->moveTo(Vector2d(-18, 3));
	vs->lineTo(Vector2d(-6, -3));
	vs->lineTo(Vector2d(-3, -9));
	vs->lineTo(Vector2d(3, -9));
	vs->lineTo(Vector2d(6, -3));
	vs->lineTo(Vector2d(18, 3));
	vs->lineTo(Vector2d(9, 9));
	vs->lineTo(Vector2d(-9, 9));
	vs->lineTo(Vector2d(-18, 3));
	vs->moveTo(Vector2d(-6, -3));
	vs->lineTo(Vector2d(6, -3));

	// initialize timer to shoot after 2-5 seconds
	int time = rand() % 3 + 2;
	shootTimer = Timer::createTimer(time, [&]() {
		shoot();
	});

	// initialize timer to turn after 3-8 seconds
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

MrBill::~MrBill()
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

void MrBill::handleCollision(const Thing *other)
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
void MrBill::die()
{
	Particle::explode(this);

	Thing::die();
}

// MrBill is worth 1000 points
int MrBill::getPoints() const
{
	return 1000;
}

// Shoot toward the player (with some error), and then reload to shoot again in 2-5 seconds
void MrBill::shoot()
{
	const double pi = 3.1415926;

	// aim toward player
	Vector2d dir = (player->getPosition() - x).normalize();

	// figure out what angle that direction is
	double ang = atan2(dir.getX(), -dir.getY());

	// add an error to it
	ang += (rand() % 20 - 10) * pi / 180.0; // error is +/- 10 degrees

	// convert back to a vector
	dir = Vector2d(sin(ang), -cos(ang));

	// shoot the bullet
	new Bullet(x + 40 * dir, dir);

	// re-load the timer to shoot again
	int time = rand() % 3 + 2; // 2 - 5 seconds
	shootTimer = Timer::createTimer(time, [&]() {
		shoot();
	});
}

// Turn in a random direction
void MrBill::turn()
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
void MrBill::retreat()
{
	retreating = true;

	// move to the right
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
