#include "Graphics.h"
#include "Vector2d.h"

#include "Ball.h"


// Constructors -- set up the ball's shape and give it an initial position and velocity
Ball::Ball()
{
	// initial position and velocity
	x = Vector2d(10, 10);
	v = Vector2d(40, 30);

	// make the ball a 10x10 square
	shape.setSize(sf::Vector2f(10, 10));
}

// Getter functions
const Vector2d Ball::getX() const
{
	return x;
}

const Vector2d Ball::getV() const
{
	return v;
}

// Move the ball based on velocity and elapsed time
// Input: dt = elapsed time
void Ball::move(double dt)
{
	// calculate new position
	x += v*dt;
}

// Draw the ball
// Input: target = window to draw on
void Ball::draw(sf::RenderTarget& target)
{
	// translate to ball's current position
	sf::Transform transform;
	transform.translate((float)x.getX(), (float)x.getY());

	// draw it there
	target.draw(shape, transform);
}