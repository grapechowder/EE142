// Class to represent our ball.

#pragma once

#include <VMIGame/MovingThing.hpp>
#include <VMIGame/Thing.hpp>

class Ball :
	public vmi::MovingThing
{
public:
	Ball();
	~Ball();

	// handle collisions with other things
	void handleCollision(const vmi::Thing* other);

	// serve the ball
	void serve(const vmi::Vector2d& position, const vmi::Vector2d& dir);

private:
	// bounce off an object, in the given direction
	void bounce(const vmi::Vector2d& n);
};

