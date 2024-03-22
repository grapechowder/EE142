#include <Keyboard.hpp>
#include <MovingThing.hpp>
#include <PolygonShape.hpp>
#include <Game.hpp>

#include "Paddle.h"
#include "Wall.h"
#include "Ball.h"

using namespace vmi;

Paddle::Paddle(const Vector2d &position, const Vector2d &normal,
               Key up, Key down)
    : MovingThing(position, Vector2d(), Vector2d(), new PolygonShape()),
      n(normal), upKey(up), downKey(down)
{
    	// build the shape as a 20x80 square
	PolygonShape *polygon = dynamic_cast<PolygonShape*>(shape);

	polygon->addPoint(Vector2d(0, 0));
	polygon->addPoint(Vector2d(19, 0));
	polygon->addPoint(Vector2d(19, 79));
	polygon->addPoint(Vector2d(0, 79));
	polygon->setFill(Color::White);
}

Paddle::~Paddle()
{
    delete shape;
}

void Paddle::move(double dt)
{
       // set velocity based on keyboard controls
       if (Game::isKeyPressed(upKey)) {
              // move upwards
              v.setY(-paddleSpeed);
       }
 
       else if (Game::isKeyPressed(downKey)) {
              // move downwards
              v.setY(paddleSpeed);
       }
 
       else {
              // neither key, so stop
              v.setY(0);
       }
 
       // now move
       MovingThing::move(dt);
}



// Check for collision
void Paddle::handleCollision(const Thing *other)
{
    if (typeid(*other) == typeid(Wall)) {
        
       v.setY(0);
       
       
    }	
}



//return n
const Vector2d Paddle::getNormal() const
{
	return n;
}
