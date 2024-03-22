// Class to represent one of the paddles in our Pong
#pragma once
#include "Graphics.h"

#include "Vector2d.h"
#include "Wall.h"

class Paddle
{
public:
            Paddle(const Vector2d& _x, const Vector2d& _n,
                        sf::Keyboard::Key _upKey, sf::Keyboard::Key _downKey);

            // Getters
            const Vector2d getX() const;
            const Vector2d getUl() const;
            const Vector2d getLr() const;
            const Vector2d getNormal() const;
            

            // move the paddle
            void move(double dt);

            // is paddle touching a wall?
            bool isCollidingWith(const Wall& wall) const;

            // handle a collision with a wall
            void handleCollision(const Wall& wall);

            // draw the paddle
            void draw(sf::RenderTarget& target);

            int getScore() const;               // returns current score for this player
            void scorePoint();                    // add a point to player’s score

private:
            Vector2d x;                             // position
            Vector2d v;                             // current velocity
            Vector2d size;                         // size of paddle
            Vector2d n;                             // normal vector from paddle
            sf::RectangleShape shape;    // rectangle shape
            sf::Keyboard::Key upKey;       // key to move paddle upwards
            sf::Keyboard::Key downKey;  // key to move downwards

            const double paddleSpeed = 400.0;   // how fast the paddle can move
            int score;                     // score for this player
};