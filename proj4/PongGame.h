// Our Pong Game
#pragma once

#include <VMIGame/Game.hpp>

#include "Ball.h"
#include "Wall.h"


class PongGame : public vmi::Game
{
public:
	PongGame();
	~PongGame();

	void update(double dt);

	bool isOver() const;

private:
	Ball *ball;
	Wall *topWall;
	Wall *bottomWall;
	Wall *leftWall;
	Wall *rightWall;

	bool done;
};

