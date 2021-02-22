// Our Pong Game
#include <VMIGame/Game.hpp>
#include <VMIGame/Vector2d.hpp>
#include <VMIGame/Keyboard.hpp>
#include <VMIGame/Color.hpp>

#include "PongGame.h"
#include "Ball.h"
#include "Wall.h"

using namespace vmi;


// Create the game window
PongGame::PongGame() : Game("Pong-ish", 640, 480), done(false)
{
	// create the ball
	ball = new Ball();

	// create the walls
	topWall = new Wall(Vector2d(0, 0), Vector2d(639, 1), Vector2d(0, 1));
	bottomWall = new Wall(Vector2d(0, 478), Vector2d(639, 479), Vector2d(0, -1));
	leftWall = new Wall(Vector2d(0, 1), Vector2d(1, 478), Vector2d(1, 0));
	rightWall = new Wall(Vector2d(638, 1), Vector2d(639, 478), Vector2d(-1, 0));

	// serve the ball
	ball->serve(Vector2d(100, 240), Vector2d(1, 0));
}


PongGame::~PongGame()
{
	delete ball;
	delete topWall;
	delete bottomWall;
	delete leftWall;
	delete rightWall;

}


// Per-frame update for game play
void PongGame::update(double dt)
{
	// intentionally blank
}

// Whether or not the game is over
bool PongGame::isOver() const
{
	return done;
}