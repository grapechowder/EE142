#pragma once

/*
* This class represents the ball in our Pong game.
*/

#include "Graphics.h"
#include "Vector2d.h"


class Ball
{
public:
	// Constructors
	Ball();

	// Getters
	const Vector2d getX() const;
	const Vector2d getV() const;

	// Move the ball to a new position based on velocity and elapsed time
	void move(double dt);

	// Draw the ball 
	void draw(sf::RenderTarget& target);

private:
	Vector2d x;						// position
	Vector2d v;						// velocity
	sf::RectangleShape shape;		// SFML shape
};

