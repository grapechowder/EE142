// Our clone of the Asteroids game

#include <Game.hpp>
#include <Vector2d.hpp>
#include <Timer.hpp>
#include <Keyboard.hpp>
#include <Color.hpp>

#include "AsteroidsGame.h"
#include "Wall.h"
#include "Player.h"
#include "Asteroid.h"
#include "Sluggo.h"
#include "MrBill.h"

using namespace vmi;

// Create the window, create the characters
AsteroidsGame::AsteroidsGame() : Game("Shoot 'em up - pew pew pew!", 800, 600), player(nullptr),
								 sluggo(nullptr), mrbill(nullptr), asteroidTimer(nullptr), sluggoTimer(nullptr),
								 mrbillTimer(nullptr), done(false)
{
	startLevel();
}

AsteroidsGame::~AsteroidsGame()
{
}

// Per-frame update
void AsteroidsGame::update(double dt)
{
	// any asteroids left?
	if (asteroidTimer == nullptr && Asteroid::getCount() == 0)
	{
		createAsteroids();
	}

	// is Sluggo alive?
	if (sluggo != nullptr && !sluggo->isAlive())
	{
		// make a new one
		createSluggo(rand() % 5 + 10);
	}

	// is Mr Bill alive?
	if (mrbill != nullptr && !mrbill->isAlive())
	{
		// make a new one
		createMrBill(rand() % 5 + 10);
	}

	// is player dead?
	if (!player->isAlive())
	{
		// display msg and wait for user
		Key response;

		do
		{
			response = createMessage("Play Again (Y/N)?", Vector2d(200, 200), 60, Color::Yellow);
		} while (response != Key::Y && response != Key::N);

		// do we reset the level and play again?
		if (response == Key::Y)
		{
			// cancel all timers
			Timer::cancelAllTimers();

			// kill everyone
			Thing::killAllThings();

			// and re-start
			startLevel();
		}
		else
		{
			done = true;
		}
	}
}

// Whether or not the game is over
bool AsteroidsGame::isOver() const
{
	return done;
}

// Start the game
void AsteroidsGame::startLevel()
{
	// create the 4 walls just outside the window
	new Wall(Vector2d(-150, -150), 1100, 100, Vector2d(0, 650)); // top wall
	new Wall(Vector2d(850, -150), 100, 900, Vector2d(-850, 0));	 // right wall
	new Wall(Vector2d(-150, 650), 1100, 100, Vector2d(0, -650)); // bottom wall
	new Wall(Vector2d(-150, -150), 100, 900, Vector2d(850, 0));	 // left wall

	// create the player
	player = new Player(Vector2d(400, 300));

	// create the asteroids
	createAsteroids();

	// create Sluggo after 15-20 sec
	createSluggo(rand() % 5 + 15);

	// create Mr Bill after 20-25 seconds
	createMrBill(rand() % 5 + 20);
}

// Create 4 big asteroids after a 1-second delay
void AsteroidsGame::createAsteroids()
{
	asteroidTimer = Timer::createTimer(1.0, [&]() {
		// put asteroids in random locations in each quadrant
		new Asteroid(Vector2d(rand() % 350, rand() % 250));
		new Asteroid(Vector2d(rand() % 350 + 450, rand() % 250));
		new Asteroid(Vector2d(rand() % 250, rand() % 250 + 350));
		new Asteroid(Vector2d(rand() % 350 + 450, rand() % 250 + 350));
		asteroidTimer = nullptr; // reset so we'll know to make more later
	});
}

// Create Sluggo
void AsteroidsGame::createSluggo(int delayTime)
{
	sluggo = nullptr;

	// create Sluggo after a delay
	sluggoTimer = Timer::createTimer(delayTime, [&]() {
		sluggo = new Sluggo();

		// delete the timer
		sluggoTimer = nullptr;
	});
}

// Create Mr Bill
void AsteroidsGame::createMrBill(int delayTime)
{
	mrbill = nullptr;

	// create Mr Bill after a delay
	mrbillTimer = Timer::createTimer(delayTime, [&]() {
		mrbill = new MrBill(player);

		// delete the timer
		mrbillTimer = nullptr;
	});
}
