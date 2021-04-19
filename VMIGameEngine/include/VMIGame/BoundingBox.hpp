// Class to represent a bounding box around an object. Bounding boxes can be used
// for collision detection.
#pragma once
#ifndef VMI_GAME_BOUNDING_BOX_H
#define VMI_GAME_BOUNDING_BOX_H

#include "Vector2d.hpp"

namespace vmi {

class BoundingBox
{
public:
	BoundingBox() { }
	BoundingBox(const Vector2d& _ul, const Vector2d& _lr) : ul(_ul), lr(_lr) {}
	BoundingBox(const Vector2d& _ul, double width, double height) : ul(_ul), lr(_ul+Vector2d(width,height)) {}

	bool intersects(const BoundingBox& other) const {
		return (ul.getX() <= other.lr.getX()) && (ul.getY() <= other.lr.getY())
			&& (other.ul.getX() <= lr.getX()) && (other.ul.getY() <= lr.getY());
	}
	bool contains(const Vector2d& point) const {
		return (ul.getX() <= point.getX()) && (ul.getY() <= point.getY())
			&& (point.getX() <= lr.getX()) && (point.getY() <= lr.getY());
	}

	// Getter functions
	const Vector2d getUl() const { return ul; }
	const Vector2d getLr() const { return lr; }
    double getWidth() const { return lr.getX() - ul.getX(); }
    double getHeight() const { return lr.getY() - ul.getY(); }

	// overloaded operators
	BoundingBox& operator+=(const BoundingBox& rhs);
	BoundingBox& operator+=(const Vector2d& rhs);

	friend const BoundingBox operator+(BoundingBox lhs, const BoundingBox& rhs) {
		lhs += rhs;
		return lhs;
	}
	friend const BoundingBox operator+(BoundingBox box, const Vector2d& point) {
		box += point;
		return box;
	}
	friend const BoundingBox operator+(const Vector2d& point, BoundingBox box) {
		box += point;
		return box;
	}
private:
	Vector2d ul;		// coordinate of upper-left corner
	Vector2d lr;		// coordinate of lower-right corner
};

// Add two bounding boxes -- this results in a new box that
// completely encloses both of the other boxes
inline BoundingBox& BoundingBox::operator+=(const BoundingBox& rhs)
{
	// find minimum x and y values
	double minX = (ul.getX() < rhs.ul.getX()) ? ul.getX() : rhs.ul.getX();
	double minY = (ul.getY() < rhs.ul.getY()) ? ul.getY() : rhs.ul.getY();

	// find maximum x and y values
	double maxX = (lr.getX() > rhs.lr.getX()) ? lr.getX() : rhs.lr.getX();
	double maxY = (lr.getY() > rhs.lr.getY()) ? lr.getY() : rhs.lr.getY();

	// update the bounds
	ul.setX(minX);
	ul.setY(minY);
	lr.setX(maxX);
	lr.setY(maxY);

	return *this;
}

// Add a point to a bounding box -- this results in a new box that
// includes the point
inline BoundingBox& BoundingBox::operator+=(const Vector2d& rhs)
{
	// find minimum x and y values
	double minX = (ul.getX() < rhs.getX()) ? ul.getX() : rhs.getX();
	double minY = (ul.getY() < rhs.getY()) ? ul.getY() : rhs.getY();

	// find maximum x and y values
	double maxX = (lr.getX() > rhs.getX()) ? lr.getX() : rhs.getX();
	double maxY = (lr.getY() > rhs.getY()) ? lr.getY() : rhs.getY();

	// update the bounds
	ul.setX(minX);
	ul.setY(minY);
	lr.setX(maxX);
	lr.setY(maxY);

	return *this;
}

} // namespace vmi

#endif