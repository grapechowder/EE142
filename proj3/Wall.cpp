/*
 * Class to represent a wall in the Pong game.
 */
 
#include "Graphics.h"
 
#include "Vector2d.h"
#include "Wall.h"
 
// Constructor
Wall::Wall(const Vector2d& ul, const Vector2d& size, const Vector2d& normal)
{
    this->ul = ul;
    lr = ul + size - Vector2d(1, 1);
    n = normal;
   
    // initialize the shape
    shape.setSize(sf::Vector2f((float) size.getX(), (float) size.getY()));
    shape.setPosition((float) ul.getX(), (float) ul.getY());
    shape.setFillColor(sf::Color::Cyan);
}
 
// Getters
const Vector2d Wall::getUl() const
{
    return ul;
}
 
const Vector2d Wall::getLr() const
{
    return lr;
}
 
const Vector2d Wall::getNormal() const
{
    return n;
}

// Draw the wall
// Input: target = window to draw in
void Wall::draw(sf::RenderTarget& target)
{
    target.draw(shape);
}