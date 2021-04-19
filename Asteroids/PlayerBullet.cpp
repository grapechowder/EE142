// Class to represent the bullet. Bullet is drawn as a small rectangle, and bullets have a
// limited lifespan. The bullet also keeps a reference to who fired it, needed for scoring points

#include <cmath>

#include <Thing.hpp>
#include <MovingThing.hpp>
#include <Vector2d.hpp>
#include <VertexShape.hpp>
#include <Timer.hpp>
#include <Color.hpp>

#include "Wall.h"
#include "Player.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Sluggo.h"
#include "MrBill.h"

#include "PlayerBullet.h"

using namespace vmi;

PlayerBullet::PlayerBullet(Vector2d position, Vector2d dir, Player *_player)
	: Bullet(position, dir), player(_player)
{
	// delete the shape and make a new one (we want a different color)
	delete shape;
	VertexShape *vs = new VertexShape();
	vs->moveTo(Vector2d(0, 5), Color::Green);
	vs->lineTo(Vector2d(0, -5), Color::Green);
	shape = vs;
}

PlayerBullet::~PlayerBullet()
{
	// intentionally blank (shape is deleted in Bullet destructor)
}

// If we hit anything other than the player, then score a point
void PlayerBullet::handleCollision(const Thing *other)
{
	// if we hit a wall, then wraparound to new location
	if (typeid(*other) == typeid(Wall))
	{
		const Wall *wall = dynamic_cast<const Wall *>(other);

		// add offset vector from wall
		x += wall->getOffset();
	}

	// hit an asteroid?
	else if (typeid(*other) == typeid(Asteroid))
	{
		const Asteroid *asteroid = dynamic_cast<const Asteroid *>(other);

		player->addPoints(asteroid->getPoints());

		// and the bullet is done for
		die();
	}

	// hit Sluggo?
	else if (typeid(*other) == typeid(Sluggo))
	{
		const Sluggo *sluggo = dynamic_cast<const Sluggo *>(other);

		player->addPoints(sluggo->getPoints());

		die();
	}

	// hit Mr. Bill?
	else if (typeid(*other) == typeid(MrBill))
	{
		const MrBill *mrbill = dynamic_cast<const MrBill *>(other);

		player->addPoints(mrbill->getPoints());

		die();
	}
}
