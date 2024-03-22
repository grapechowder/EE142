/*
 * Class to represent a wall in the Pong game.
 */
 #pragma once

#include "Graphics.h"
#include "Vector2d.h"

class Wall
{
public:
    // Construtors
    Wall(const Vector2d& ul, const Vector2d& size, const Vector2d& normal);

    // Getters
    const Vector2d getUl() const;
    const Vector2d getLr() const;
    const Vector2d getNormal() const;
   
    // draw the wall
    void draw(sf::RenderTarget& target);

private:
    Vector2d ul;                    // location of upper-left corner of wall
    Vector2d lr;                    // location of lower-right corner of wall
    Vector2d n;                     // normal vector perpendicular to wall
    sf::RectangleShape shape;       // SFML shape
};