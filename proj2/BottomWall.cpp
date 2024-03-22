/*
 * Class to represent the top wall in the Pong game.
 */
 #include "Graphics.h"
 #include "Vector2d.h"
 #include "BottomWall.h"
  
 // Constructor
 BottomWall::BottomWall()
 {
    // wall goes from (0,0) to (639, 1)
    ul = Vector2d(0, 478);
    lr = Vector2d(639, 479);
      
    // initialize the shape
    shape.setSize(sf::Vector2f(640, 2));
    shape.setPosition(0, 478);             // same coordinates as bottom left corner
    shape.setFillColor(sf::Color::Cyan);
 }
  
 // Getters
 const Vector2d BottomWall::getUl() const
 {
    return ul;
 }
  
 const Vector2d BottomWall::getLr() const
 {
    return lr;
 }
  
 // Draw the wall
 // Input: target = window to draw in
 void BottomWall::draw(sf::RenderTarget& target)
 {
     target.draw(shape);
 }