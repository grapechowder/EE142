/*
 * Class to represent the top wall in the Pong game.
 */
#pragma once
#include "Graphics.h"
#include "Vector2d.h"
 
class TopWall
{
public:
   // Constructors
   TopWall();
  
   // getters
   const Vector2d getUl() const;
   const Vector2d getLr() const;
 
   // draw the wall
   void draw(sf::RenderTarget& target);
  
private:
   Vector2d ul; // location of upper-left corner of wall
   Vector2d lr; // location of lower-right corner of wall
   sf::RectangleShape shape; // SFML shape
};