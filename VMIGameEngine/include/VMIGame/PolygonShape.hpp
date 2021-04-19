// Class to represent polygon shapes, stored as a list
// of vertexes
#pragma once
#ifndef VMI_GAME_POLYGON_SHAPE_H
#define VMI_GAME_POLYGON_SHAPE_H

#include <vector>
#include "Graphics.hpp"

#include "Vector2d.hpp"
#include "BoundingBox.hpp"
#include "Shape.hpp"
#include "Color.hpp"

namespace vmi {

class PolygonShape :
	public Shape
{
public:
	PolygonShape() {}
	PolygonShape(std::vector<Vector2d> _points);
	PolygonShape(const PolygonShape& other);

	~PolygonShape() {}

	PolygonShape& operator=(const PolygonShape& other);
    
	// Draw the polygon
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
#ifndef ZYBOOKS		
		target.draw(polygon, states);
#endif		
	}


	// Get a bounding box around the shape
	const BoundingBox getBounds() const { return bounds; }

	// Add points to polygon
	void addPoint(const Vector2d point);
	void addPoints(const std::vector<Vector2d> _points) {
		for (auto it = _points.cbegin(); it != _points.cend(); ++it) {
			addPoint(*it);
		}
	}

	// Specify the fill color
	void setFill(Color color) {
		polygon.setFillColor(sf::Color(static_cast<sf::Uint32>(color)));
	}

	// Specify the outline color
	void setOutline(Color color) {
		polygon.setOutlineColor(sf::Color(static_cast<sf::Uint32>(color)));
	}

private:
	std::vector<Vector2d> points;
	BoundingBox bounds;

	sf::ConvexShape polygon;
};

// Constructor -- add points to the shape
inline PolygonShape::PolygonShape(std::vector<Vector2d> _points) : points(_points)
{
	// add points to the SFML polygon
#ifndef ZYBOOKS	
	polygon.setPointCount(points.size());
#endif
	int i = 0;
	for (auto it = points.cbegin(); it != points.cend(); ++it) {
		// add point to the SFML shape
#ifndef ZYBOOKS	
		polygon.setPoint(i, sf::Vector2f((float) (*it).getX(), (float) (*it).getY()));
#endif
		// also add it to our bounding box
		bounds += *it;

		// increment index
		i++;
	}
}

// Copy constructor
inline PolygonShape::PolygonShape(const PolygonShape& other) : points(other.points), bounds(other.bounds)
{
	// copy the shape (SFML doesn't provide a copy constructor
#ifndef ZYBOOKS	
	polygon.setPointCount(points.size());
#endif
	int i = 0;
	for (auto it = points.cbegin(); it != points.cend(); ++it) {
		// add point to polygon
#ifndef ZYBOOKS	
		polygon.setPoint(i, sf::Vector2f((float) (*it).getX(), (float) (*it).getY()));
#endif
		// also add it to our bounding box
		bounds += *it;

		// increment index
		i++;
	}
}

// Assignment operator
inline PolygonShape& PolygonShape::operator=(const PolygonShape& other)
{
	if (this != &other) {
		points = other.points;

		// copy the shape (SFML doesn't provide a copy constructor
#ifndef ZYBOOKS	
		polygon.setPointCount(points.size());
#endif		
		int i = 0;
		for (auto it = points.cbegin(); it != points.cend(); ++it) {
			// add point to polygon
#ifndef ZYBOOKS	
			polygon.setPoint(i, sf::Vector2f((float) (*it).getX(), (float) (*it).getY()));
#endif

			// also add it to our bounding box
			bounds += *it;

			// increment index
			i++;
		}
	}

	return *this;
}

// Add points to polygon
inline void PolygonShape::addPoint(const Vector2d point)
{
#ifndef ZYBOOKS	
	// add it to my list
	points.push_back(point);
#endif
	// add it to my bounding box
	bounds += point;

	// add it to the SFML shape
#ifndef ZYBOOKS	
	polygon.setPointCount(points.size());
	polygon.setPoint(points.size() - 1, sf::Vector2f((float) point.getX(), (float) point.getY()));
#endif	
}

} // namespace vmi
#endif