// Mr. Bill is the smaller alien spaceship. He has two different states to be in -- attacking or retreating.
// When attacking, he moves in a random fashion, and fires a bullet every once in a while. He aims
// his bullets toward the player's ship. After a while, he goes to retreat mode, where he moves
// off the right side of the screen. He then disappears.
//
// To get the random motion, we pick a velocity in a random direction, and then set a timer to go off
// to change the direction. We also use timers to decide when to change state.

#pragma once

#include <Vector2d.hpp>
#include <MovingThing.hpp>
#include <Thing.hpp>
#include <Timer.hpp>

#include "Player.h"

class MrBill : public vmi::MovingThing
{
public:
	MrBill(const Player *player);
	~MrBill();

	void handleCollision(const vmi::Thing *other);

	void die();

	int getPoints() const;

private:
	bool retreating;			   // whether or not we're retreating
	vmi::Vector2d retreatVelocity; // speed and direction when retreating
	vmi::Timer *shootTimer;		   // when to shoot next
	vmi::Timer *turnTimer;		   // when to change direction
	vmi::Timer *retreatTimer;	   // when to retreat

	const Player *player; // need to know where the player is to aim

	void turn();	// change direction
	void shoot();	// shoot a bullet
	void retreat(); // run away!
};
