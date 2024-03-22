/*
 * Class to represent the Left wall in the Pong game.
 */
 #include "Graphics.h"
 #include "Vector2d.h"
 #include "LeftWall.h"
  
 // Constructor
 LeftWall::LeftWall()
 {
    // wall goes from (0,0) to (1,479)
    ul = Vector2d(0, 0);
    lr = Vector2d(1, 479);
      
    // initialize the shape
    shape.setSize(sf::Vector2f(2, 480));
    shape.setPosition(0, 0);             // same coordinates as ul
    shape.setFillColor(sf::Color::Red);
 }
  
 // Getters
 const Vector2d LeftWall::getUl() const
 {
    return ul;
 }
  
 const Vector2d LeftWall::getLr() const
 {
    return lr;
 }
  
 // Draw the wall
 // Input: target = window to draw in
 void LeftWall::draw(sf::RenderTarget& target)
 {
     target.draw(shape);
 }