/*
 * Class to represent the top wall in the Pong game.
 */
 #include "Graphics.h"
 #include "Vector2d.h"
 #include "RightWall.h"
  
 // Constructor
 RightWall::RightWall()
 {
    // wall goes from (0,0) to (639, 1)
    ul = Vector2d(638, 0);
    lr = Vector2d(639, 479);
      
    // initialize the shape
    shape.setSize(sf::Vector2f(2, 480));
    shape.setPosition(639, 479);             // same coordinates as upper left corner
    shape.setFillColor(sf::Color::Red);
 }
  
 // Getters
 const Vector2d RightWall::getUl() const
 {
    return ul;
 }
  
 const Vector2d RightWall::getLr() const
 {
    return lr;
 }
  
 // Draw the wall
 // Input: target = window to draw in
 void RightWall::draw(sf::RenderTarget& target)
 {
     target.draw(shape);
 }