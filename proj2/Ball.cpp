#include "Graphics.h"
#include "Vector2d.h"
#include "Wall.h"
 
#include "Ball.h"
 
 
// Constructors -- set up the ball's shape and give it an
//                 initial position and velocity
Ball::Ball()
{
    // initial position and velocity
    x = Vector2d(10, 10);
    v = Vector2d(140, 130);
 
    // make the ball a 10x10 square
    shape.setSize(sf::Vector2f(10, 10));
}
 
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