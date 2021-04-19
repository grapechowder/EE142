// Our clone of the Asteroids game
#pragma once

#include <Game.hpp>
#include <Timer.hpp>

#include "Player.h"
#include "Sluggo.h"
#include "MrBill.h"

class AsteroidsGame : public vmi::Game
{
public:
	AsteroidsGame();
	~AsteroidsGame();

	void update(double dt);

	bool isOver() const;

private:
	Player *player;
	Sluggo *sluggo;
	MrBill *mrbill;

	vmi::Timer *asteroidTimer;
	vmi::Timer *sluggoTimer;
	vmi::Timer *mrbillTimer;

	bool done;

	void startLevel();
	void createAsteroids();
	void createSluggo(int delayTime);
	void createMrBill(int delayTime);
};
