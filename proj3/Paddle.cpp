// Class to represent a paddle
#include "Graphics.h"

#include "Vector2d.h"
#include "Wall.h"
#include "Paddle.h"

// Constructor
Paddle::Paddle(const Vector2d& _x, const Vector2d& _n,
                        sf::Keyboard::Key _upKey, sf::Keyboard::Key _downKey)
                                : x(_x), v(Vector2d()), n(_n), upKey(_upKey),
                                            downKey(_downKey),score(0)
{
   size = Vector2d(20, 80);

   // set up the shape
   shape.setSize(sf::Vector2f((float) size.getX(), (float) size.getY()));
}


// Getters
const Vector2d Paddle::getX() const
{

    return x;
}

const Vector2d Paddle::getUl() const
{
    return x;                       // position is same as upper left
}

const Vector2d Paddle::getLr() const
{
    return x + size - Vector2d(1, 1);
}


const Vector2d Paddle::getNormal() const
{
    return n;
}

int Paddle::getScore() const
{
   return score;
}

// move the paddle
void Paddle::move(double dt)
{
  if (sf::Keyboard::isKeyPressed(upKey)) {
        // move upwards
        v.setY(-paddleSpeed);
   }
   else if (sf::Keyboard::isKeyPressed(downKey)) {
        // move downwards
        v.setY(paddleSpeed);
   }
   else {
        v.setY(0);
    }

    // calculate new position
    x += v*dt;
}


// is paddle touching a wall?
bool Paddle::isCollidingWith(const Wall& wall) const
{
    Vector2d myUl = getUl();
    Vector2d myLr = getLr();
    Vector2d wallUl = wall.getUl();
    Vector2d wallLr = wall.getLr();

    return (myUl.getX() < wallLr.getX())
        && (myUl.getY() < wallLr.getY())
        && (wallUl.getX() < myLr.getX())
        && (wallUl.getY() < myLr.getY());
}


// handle a collision with a wall
void Paddle::handleCollision(const Wall& wall)
{
   // stop moving
    v.setY(0);

    // move backwards a little bit
    x += 10 * wall.getNormal();
}


// draw the paddle
void Paddle::draw(sf::RenderTarget& target)
{
    // translate to paddle's current position
    sf::Transform transform;
    transform.translate((float)x.getX(), (float)x.getY());

    // draw it there
    target.draw(shape, transform);
}

void Paddle::scorePoint()
{
   // add  point to the score
   score++;
}