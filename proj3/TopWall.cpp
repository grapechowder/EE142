/*
 * Class to represent the top wall in the Pong game.
 */
#include "Graphics.h"
#include "Vector2d.h"
#include "TopWall.h"
 
// Constructor
TopWall::TopWall()
{
   // wall goes from (0,0) to (639, 1)
   ul = Vector2d(0, 0);
   lr = Vector2d(639, 1);
     
   // initialize the shape
   shape.setSize(sf::Vector2f(640, 2));
   shape.setPosition(0, 0);             // same coordinates as upper-left corner
   shape.setFillColor(sf::Color::Yellow);
}
 
// Getters
const Vector2d TopWall::getUl() const
{
   return ul;
}
 
const Vector2d TopWall::getLr() const
{
   return lr;
}
 
// Draw the wall
// Input: target = window to draw in
void TopWall::draw(sf::RenderTarget& target)
{
    target.draw(shape);
}