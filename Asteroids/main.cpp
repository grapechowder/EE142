// For our Asteroids clone

#include "AsteroidsGame.h"

using namespace vmi;

int main(void)
{
	AsteroidsGame game;

	game.playGame();

	return 0;
}

// The following lines are for auto-grading on zyBooks. Do not modify!
#ifdef ZYBOOKS

#include "Asteroid.cpp"
#include "AsteroidsGame.cpp"
#include "Bullet.cpp"
#include "Particle.cpp"
#include "Player.cpp"
#include "PlayerBullet.cpp"
#include "Wall.cpp"

#endif
