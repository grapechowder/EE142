#include "Graphics.h"
#include "Vector2d.h"
#include "Ball.h"
#include "Wall.h"
 
const int windowWidth = 640;
const int windowHeight = 480;
 
int main()
{
    // create a new window to display the game
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),"Holy crap it woerked");
 
    // get a clock we can use to measure elapsed time
    sf::Clock clock;
 
    // Create the ball
    Ball ball;
   
    // Create the walls
    Wall topWall(Vector2d(0, 0), Vector2d(windowWidth, 2), Vector2d(0, 1));
    Wall bottomWall(Vector2d(0, windowHeight-2), Vector2d(windowWidth, 2),
                                   Vector2d(0, -1));
    Wall leftWall(Vector2d(0, 0), Vector2d(2, windowHeight), Vector2d(1, 0));
    Wall rightWall(Vector2d(windowWidth-2, 0), Vector2d(2, windowHeight),
                                   Vector2d(-1, 0));
 
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
        dt = (dt > 0.04) ? 0.04 : dt;              // make sure dt is a sane value
 
        // move everything
        ball.move(dt);
       
        // check for collisions
        if (ball.isCollidingWith(topWall)) {
            ball.bounce(topWall.getNormal());
        }
        if (ball.isCollidingWith(bottomWall)) {
            ball.bounce(bottomWall.getNormal());
        }
        if (ball.isCollidingWith(leftWall)) {
            ball.bounce(leftWall.getNormal());
        }
        if (ball.isCollidingWith(rightWall)) {
            ball.bounce(rightWall.getNormal());
        }
 
        // erase everything in the window
        window.clear();
 
        // draw everything in new locations
        ball.draw(window);
        topWall.draw(window);
        bottomWall.draw(window);
        leftWall.draw(window);
        rightWall.draw(window);
 
        // display the updated window
        window.display();
    }
 
    return 0;
}
