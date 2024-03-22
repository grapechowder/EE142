// Our Pong Game
#include <Game.hpp>
#include <Vector2d.hpp>
#include <Keyboard.hpp>
#include <Color.hpp>

#include "PongGame.h"
#include "Ball.h"
#include "Wall.h"
#include "Paddle.h"

using namespace vmi;


// Create the game window
PongGame::PongGame() : Game(" god please Make it stop", 640, 480), done(false)
{
	// create the ball
	ball = new Ball();

	// create the walls
	topWall = new Wall(Vector2d(0, 0), Vector2d(639, 1), Vector2d(0, 1));
	bottomWall = new Wall(Vector2d(0, 478), Vector2d(639, 479), Vector2d(0, -1));
	leftWall = new Wall(Vector2d(0, 1), Vector2d(1, 478), Vector2d(1, 0));
	rightWall = new Wall(Vector2d(638, 1), Vector2d(639, 478), Vector2d(-1, 0));
	leftPaddle = new Paddle(Vector2d(50,200), Vector2d(1,0), Key::W, Key::S);
	rightPaddle = new Paddle(Vector2d(570,200), Vector2d(-1,0), Key::Up, Key::Down);
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
	delete rightPaddle;
	delete leftPaddle;

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