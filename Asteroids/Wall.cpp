// Class to represent a hidden wall. These walls are placed outside the visible world for Asteroids and they
// enable us to get the wraparoud motion for the characters -- when a character moves outside the window,
// it re-appears on the other side (as if the window wraps around). Each wall has an offset vector --
// a value that can be added to a character's position to move it to the other side of the window.

#include <Thing.hpp>
#include <Vector2d.hpp>
#include <BoundingBox.hpp>
#include <Color.hpp>
#include <PolygonShape.hpp>

#include "Wall.h"

using namespace vmi;

Wall::Wall(Vector2d _x, double width, double height, Vector2d _offset) : Thing(_x, new PolygonShape()), offset(_offset)
{
	// build the rectangle to represent the shape
	PolygonShape *polygon = dynamic_cast<PolygonShape *>(shape);

	polygon->addPoint(Vector2d(0, 0));
	polygon->addPoint(Vector2d(width - 1, 0));
	polygon->addPoint(Vector2d(width - 1, height - 1));
	polygon->addPoint(Vector2d(0, height - 1));
}

Wall::~Wall()
{
	delete shape;
}

// Ignore any collisions
void Wall::handleCollision(const Thing *other)
{
	// intentionally blank
}

// Return the offset for this wall -- how things should adjust their position if they hit this wall.
const Vector2d Wall::getOffset() const
{
	return offset;
}
