#include "Graphics.h"

#include "Vector2d.h"
#include "Ball.h"

const int windowWidth = 640;
const int windowHeight = 480;

int main()
{
	// create a new window to display the game
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Bouncy bouncy!");

	// get a clock we can use to measure elapsed time
	sf::Clock clock;

	// Create the ball
	Ball ball;

	// Repeat until the window is closed
	while (window.isOpen())
	{
		// handle any pending events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// get elapsed time
		double dt = clock.restart().asSeconds();
		dt = (dt > 0.04) ? 0.04 : dt;		// make sure dt is a sane value

											// move everything
		ball.move(dt);

		// erase everything in the window
		window.clear();

		// draw everything in new locations
		ball.draw(window);

		// display the updated window
		window.display();
	}

	return 0;
}
