// This class represents the player. His movement is controlled by the arrow keys.

#pragma once

#include <Graphics.hpp>

#include <Vector2d.hpp>
#include <Thing.hpp>
#include <MovingThing.hpp>
#include <VertexShape.hpp>
#include <Timer.hpp>
#include <Text.hpp>

class Player : public vmi::MovingThing
{
public:
	Player(const vmi::Vector2d &_x);
	~Player();

	// move -- we override this to handle keyboard input
	void move(double dt);

	void handleCollision(const vmi::Thing *other);

	// override this to handle multiple lives
	void die();

	// draw with score and extra lives
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	// add points to his score
	void addPoints(int points);

	// whether or not we're in flashing mode
	bool isFlashing() const;

private:
	int score;	   // player's score
	int numLives;  // number of remaining lives
	bool flashing; // when we spawn, we flash and are invisible for a while
	bool visible;  // whether or not ship is visible
	bool thrustOn; // whether or not thrusters are on
	bool shooting; // whether or not we're shooting a bullet

	vmi::Vector2d startPosition; // where we start from when we spawn
	vmi::VertexShape ship[2];	 // different images for animation

	vmi::Text scoreText; // display of current score

	vmi::Timer *flameTimer; // timer for toggling rocket flames
	vmi::Timer *flashTimer; // timer for toggling images when flashing
	vmi::Timer *shootTimer; // timer to limit time between shots

	void startFlashing();					// go to flashing mode and start animation
	void stopFlashing();					// stop flashing and return to normal mode
	vmi::Vector2d getForwardVector() const; // returns vector in direction we're facing
	void toggleRocketFlames();				// switches shapes to show/hide rocket flames
	void shoot(vmi::Vector2d dir);			// shoot a bullet
	void hyperspace();						// jump to hyperspace
};
