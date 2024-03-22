#include "Graphics.h"
#include "Vector2d.h"
#include "Wall.h"
#include "Paddle.h"
#include "Ball.h"

#include <cstdlib> 
 
 
// Constructors -- set up the ball's shape and give it an
//                 initial position and velocity
Ball::Ball()
{

    shape.setSize(sf::Vector2f(10, 10));
}

// Constructors -- set up the ball's shape and give it an initial position and velocity

// Getter functions
const Vector2d Ball::getX() const
{
         return x;
}
 
const Vector2d Ball::getV() const
{
         return v;
}
 
 
// Move the ball based on velocity and elapsed time
// Input: dt = elapsed time
void Ball::move(double dt)
{
    // calculate new position
    x += v*dt;
}
 
// Draw the ball
// Input: target = window to draw on
void Ball::draw(sf::RenderTarget& target)
{
    // translate to ball's current position
    sf::Transform transform;
    transform.translate((float) x.getX(), (float) x.getY());
 
    // draw it there
    target.draw(shape, transform);
}
 
// Is the ball colliding with another object?
// Input: wall = are we hitting this wall?
// Returns true if ball is colliding with this wall
bool Ball::isCollidingWith(const Wall& wall) const
{
    Vector2d myUl = x;
    Vector2d myLr = x + Vector2d(9, 9);
    Vector2d hisUl = wall.getUl();
    Vector2d hisLr = wall.getLr();
   
    return (myUl.getX() < hisLr.getX()) && (myUl.getY() < hisLr.getY())
              && (hisUl.getX() < myLr.getX()) && (hisUl.getY() < myLr.getY());
}
 
 
// Bounce in a specified direction
// Input: n = normal vector (direction to bounce in)
void Ball::bounce(const Vector2d& n)
{
    // move the ball backwards to get off the wall
    x += 10*n;
   
    // reverse our direction
    v -= 2*v.dot(n)*n;
}

// Is the ball colliding with another object?
// Input: paddle = are we hitting this paddle?
// Returns true if ball is colliding with this paddle
bool Ball::isCollidingWith(const Paddle& paddle) const
{
    Vector2d myUl = x;
    Vector2d myLr = x + Vector2d(9, 9);
    Vector2d hisUl = paddle.getUl();
    Vector2d hisLr = paddle.getLr();

    return (myUl.getX() < hisLr.getX()) && (myUl.getY() < hisLr.getY())
         && (hisUl.getX() < myLr.getX()) && (hisUl.getY() < myLr.getY());
}

// Serve the ball -- move to a specific location and give it a
// random velocity in the specified direction.
// Input: position = location to move to
//        dir = direction to move in
// Returns nothing
void Ball::serve(const Vector2d& position, const Vector2d& dir)
{
    // move to new location
    x = position;

    // move in the new direction -- this is some random number voodoo here
    int y_dir = (rand() % 2) * 2 - 1;       // y_dir is either -1 or 1
    double x_speed = rand() % 100 + 100;    // between 100 and 200
    double y_speed = rand() % 100 + 100;    // also between 100 and 200

    v = x_speed * dir + y_speed * Vector2d(0, y_dir);
}