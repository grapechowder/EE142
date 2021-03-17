// Class to represent the walls in our Pong game

#include <Vector2d.hpp>
#include <Thing.hpp>
#include <PolygonShape.hpp>
#include <Color.hpp>

#include "Wall.h"

using namespace vmi;

// Constructor -- build the wall with the given corners
Wall::Wall(const Vector2d& ul, const Vector2d& lr, const Vector2d& normal)
	: Thing(ul, new PolygonShape()), n(normal)
{
	// figure out size of wall
	double width = lr.getX() - ul.getX() + 1;
	double height = lr.getY() - ul.getY() + 1;

	// make the shape a rectangle
	PolygonShape* polygon = dynamic_cast<PolygonShape*>(shape);

	polygon->addPoint(Vector2d(0, 0));
	polygon->addPoint(Vector2d(width - 1, 0));
	polygon->addPoint(Vector2d(width - 1, height - 1));
	polygon->addPoint(Vector2d(0, height - 1));

	// make the wall yellow
	polygon->setFill(Color::Yellow);
}


Wall::~Wall()
{
	delete shape;
}

// Return the normal vector
const Vector2d Wall::getNormal() const
{
	return n;
}

// Handle collisions (by ignoring them!)
void Wall::handleCollision(const Thing* other)
{
	// intentionally blank
}
