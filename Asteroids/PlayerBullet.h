// Class to represent the bullet fired by the player. Bullet is drawn as a small rectangle, and bullets have a
// limited lifespan. The bullet scores points for the player when it hits something

#pragma once

#include <MovingThing.hpp>
#include <Thing.hpp>
#include <Vector2d.hpp>
#include <Timer.hpp>

#include "Bullet.h"
#include "Player.h"

class PlayerBullet : public Bullet
{
public:
	PlayerBullet(vmi::Vector2d position, vmi::Vector2d dir, Player *player);
	~PlayerBullet();

	void handleCollision(const vmi::Thing *other);

private:
	Player *player;
};
