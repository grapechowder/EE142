// This class represents the player. His movement is controlled by the arrow keys.

#include <cmath>
#include <sstream>

#include <Graphics.hpp>
#include <Vector2d.hpp>
#include <Thing.hpp>
#include <MovingThing.hpp>
#include <VertexShape.hpp>
#include <Keyboard.hpp>
#include <Game.hpp>
#include <Color.hpp>
#include <Text.hpp>

#include "Player.h"
#include "Wall.h"
#include "Bullet.h"
#include "PlayerBullet.h"
#include "Asteroid.h"
#include "Sluggo.h"
#include "MrBill.h"
#include "Particle.h"

using namespace vmi;

Player::Player(const Vector2d &_x) : MovingThing(_x,		 // position
												 Vector2d(), // velocity
												 Vector2d(), // acceleration
												 nullptr),	 // no shape yet (created below)
									 score(0),
									 numLives(4),
									 flashing(false),
									 visible(true),
									 thrustOn(false),
									 shooting(false),
									 startPosition(_x),
									 flameTimer(nullptr),
									 flashTimer(nullptr),
									 shootTimer(nullptr)
{
	// shape for the plain ship
	ship[0].moveTo(Vector2d(-15, 25));
	ship[0].lineTo(Vector2d(0, -25));
	ship[0].lineTo(Vector2d(15, 25));
	ship[0].moveTo(Vector2d(-11.25, 12.5));
	ship[0].lineTo(Vector2d(11.25, 12.5));

	// ship with flames from the thruster
	ship[1].moveTo(Vector2d(-15, 25));
	ship[1].lineTo(Vector2d(0, -25));
	ship[1].lineTo(Vector2d(15, 25));
	ship[1].moveTo(Vector2d(-11.25, 12.5));
	ship[1].lineTo(Vector2d(11.25, 12.5));
	ship[1].moveTo(Vector2d(-8, 12.5), Color::Red);
	ship[1].lineTo(Vector2d(0, 25), Color::Red);
	ship[1].lineTo(Vector2d(8, 12.5), Color::Red);

	// use plain ship to start
	shape = &ship[0];

	// set up the text display of the score
	scoreText.setText("0");
	scoreText.setCharacterSize(30);
	scoreText.setPosition(Vector2d(40, 8));
	scoreText.setFill(Color::White);

	// no animation yet
	flameTimer = nullptr;

	// not shooting
	shootTimer = nullptr;

	// start flashing at beginning of game
	startFlashing();
}

Player::~Player()
{
	// intentionally blank
}

// move -- we override this to handle keyboard input
void Player::move(double dt)
{
	// which direction are we facing?
	Vector2d forward = getForwardVector();

	// fire a bullet?
	if (Game::isKeyPressed(Key::Space))
	{
		if (!shooting)
		{
			shoot(forward);
		}
	}
	else
	{
		shooting = false;
		if (shootTimer != nullptr)
		{
			shootTimer->cancel();
		}
	}

	// don't move if we're flashing
	if (!flashing)
	{

		// check status of arrow keys
		bool leftKey = Game::isKeyPressed(Key::Left);
		bool rightKey = Game::isKeyPressed(Key::Right);

		// should we rotate?
		if (leftKey && !rightKey)
		{
			// turn left
			w = -400.0;
		}
		else if (!leftKey && rightKey)
		{
			// turn right
			w = 400.0;
		}
		else
		{
			// stop turning
			w = 0.0;
		}

		// check for thruster key
		if (Game::isKeyPressed(Key::Up))
		{
			thrustOn = true;

			// start animation of rocket engine if needed
			if (flameTimer == nullptr)
			{
				// timer is not running, so start the animation
				shape = &ship[1]; // display the flames

				// start the timer
				flameTimer = Timer::createRepeatingTimer(0.25,
														 [&]() {
															 toggleRocketFlames();
														 });
			}
		}
		else
		{
			thrustOn = false;

			// cancel rocket animation if it's running
			if (flameTimer != nullptr)
			{
				// turn flames off
				shape = &ship[0];

				// cancel the timer
				flameTimer->cancel();
				flameTimer = nullptr;
			}
		}

		// check for hyperspace
		if (Game::isKeyPressed(Key::RShift))
		{
			hyperspace();
		}

		// if rockets are on, then apply acceleration
		if (thrustOn)
		{
			a = 400.0 * forward;
		}
		else
		{
			// apply friction force
			a = -100.0 * v.normalize();

			// if we've slowed enough, then just stop
			if (v.magnitude() < 1.0)
			{
				v = Vector2d();
				a = Vector2d();
			}
		}

		// now move
		MovingThing::move(dt);

		// limit velocity
		if (v.magnitude() > 800.0)
		{
			v = 800.0 * v.normalize();
		}
	}
}

void Player::handleCollision(const Thing *other)
{
	// ignore all collisions when we're flashing
	if (!flashing)
	{
		// if we hit a wall, then wraparound to new location
		if (typeid(*other) == typeid(Wall))
		{
			const Wall *wall = dynamic_cast<const Wall *>(other);

			// add offset vector from wall
			x += wall->getOffset();
		}

		// if we hit a bullet, we're toast unless it's one of our own
		else if (typeid(*other) == typeid(Bullet) && typeid(*other) != typeid(PlayerBullet))
		{
			// we're done for
			die();
		}

		// if we hit an asteroid, it's dirt-nap time (but score points first!)
		else if (typeid(*other) == typeid(Asteroid))
		{
			const Asteroid *asteroid = dynamic_cast<const Asteroid *>(other);

			addPoints(asteroid->getPoints());

			die();
		}

		// also bad news if we hit Sluggo
		else if (typeid(*other) == typeid(Sluggo))
		{
			const Sluggo *sluggo = dynamic_cast<const Sluggo *>(other);

			addPoints(sluggo->getPoints());

			die();
		}

		// Oh no! Mr. Bill!!!
		else if (typeid(*other) == typeid(MrBill))
		{
			const MrBill *mrbill = dynamic_cast<const MrBill *>(other);

			addPoints(mrbill->getPoints());

			die();
		}
	}
}

// override this to handle multiple lives
void Player::die()
{
	numLives--;

	// we done blowed up
	Particle::explode(this);

	if (numLives <= 0)
	{
		// ok, we're really dead now
		Thing::die();
	}
	else
	{
		// go back to starting position
		startFlashing();
	}
}

// draw with score and extra lives
void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// draw the ship if we're visible
	if (visible)
	{
		Thing::draw(target, states);
	}

	// draw the extra lives
	sf::RenderStates rs = sf::RenderStates::Default;
	sf::Transform transform;

	// show extra lives as smaller ships
	transform.scale(0.5f, 0.5f).translate(75.0f, 130.0f);
	for (int i = 0; i < numLives - 1; ++i)
	{
		// move over a little to draw next ship
		transform.translate(50.0f, 0.0f);
		rs.transform = transform;

		ship[0].draw(target, rs);
	}

	// and draw the score
	scoreText.draw(target, states);
}

// Ship flashes whenever it is spawned
void Player::startFlashing()
{
	flashing = true;
	visible = true;

	// go back to start position and stop moving
	x = startPosition;
	v = Vector2d();
	a = Vector2d();
	angle = 0;
	w = 0;

	// display the ship
	shape = &ship[0];

	// set up animation timer to toggle visibility
	flashTimer = Timer::createRepeatingTimer(0.25, [&]() {
		visible = !visible; // toggle the visibility
	});

	// set up timer to go back to normal mode
	Timer::createTimer(2.0, [&]() {
		stopFlashing();
	});
}

// Stop flashing and return to normal mode
void Player::stopFlashing()
{
	flashing = false;
	visible = true;

	// cancel the animation timer so we stop flashing
	flashTimer->cancel();
}

// Returns unit vector pointing in direction ship is facing.
Vector2d Player::getForwardVector() const
{
	double angleRad = angle * 3.1415926 / 180.0; // convert rotation angle to radians

	return Vector2d(sin(angleRad), -cos(angleRad));
}

// Toggles the shape between ship[0] (no flames) and ship[1] (with flames)
void Player::toggleRocketFlames()
{
	// are we displaying ship[0]
	if (shape == &ship[0])
	{
		// switch to ship[1]
		shape = &ship[1];
	}
	else
	{
		// switch to ship[0]
		shape = &ship[0];
	}
}

// Shoot a bullet in the given direction. We also start a timer to allow us to shoot again
void Player::shoot(Vector2d dir)
{
	// shoot the bullet
	new PlayerBullet(x + 50 * dir, dir, this);

	// set flag so I can't shoot again
	shooting = true;

	// create a timer to clear the flag
	shootTimer = Timer::createTimer(0.25, [&]() {
		shooting = false;
	});
}

// Add points to the player's score
void Player::addPoints(int points)
{
	score += points;

	// update the display
	std::stringstream ss;
	ss << score;
	scoreText.setText(ss.str());
}

// Whether or not we're flashing
bool Player::isFlashing() const
{
	return flashing;
}

// Jump to hyperspace
void Player::hyperspace()
{
	// pick a random location
	x = Vector2d(rand() % 700 + 50,	 // x between 50 and 750
				 rand() % 500 + 50); // y between 50 and 550
	v = Vector2d();					 // stop moving

	// set all the flags so we stop and cancel everything
	thrustOn = false;
	flashing = true;
	visible = false;
	shooting = false;
	shape = &ship[0]; // turn off the flames

	// delay so we re-appear in 0.25 sec
	Timer::createTimer(0.25, [&]() {
		visible = true;
		flashing = false;
	});
}
