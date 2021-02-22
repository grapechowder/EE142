/*
 * Class to represent a 2-dimensional vector.
 */
#include <cmath>
#include "Vector2d.h"


// Default constructor
Vector2d::Vector2d() : x(0.0), y(0.0)
{
	// intentionally blank
}

Vector2d::Vector2d(double _x, double _y) : x(_x), y(_y)
{
	// intentionally blank
}

// Dot product
double Vector2d::dot(const Vector2d& v) const
{
	// FIXME
	return 0.0;
}

// Vector magnitude
double Vector2d::magnitude() const
{
	// FIXME
	return 0.0;
}

// Nomralized vector
const Vector2d Vector2d::normalize() const
{
	// FIXME
	return Vector2d();
}

// getters and setters
double Vector2d::getX() const
{
	return x;
}

double Vector2d::getY() const
{
	return y;
}

void Vector2d::setX(double _x)
{
	// FIXME
}

void Vector2d::setY(double _y)
{
	// FIXME
}

// overloaded operators -- assignment operators
Vector2d& Vector2d::operator+=(const Vector2d& rhs)
{
	// FIXME
	return *this;
}

Vector2d& Vector2d::operator-=(const Vector2d& rhs)
{
	// FIXME
	return *this;
}

Vector2d& Vector2d::operator*=(double c)
{
	// FIXME
	return *this;
}

// overloaded operators -- arithmetic
const Vector2d operator +(Vector2d lhs, const Vector2d& rhs)
{
	// FIXME
	return Vector2d();
}

const Vector2d operator -(Vector2d lhs, const Vector2d& rhs)
{
	// FIXME
	return Vector2d();
}

const Vector2d operator *(Vector2d lhs, double rhs)
{
	// FIXME
	return Vector2d();
}

const Vector2d operator *(double lhs, Vector2d rhs)
{
	// FIXME
	return Vector2d();
}

const Vector2d Vector2d::operator-()
{
	// FIXME
	return Vector2d();
}



// overloaded operators -- comparisons
bool operator ==(const Vector2d& v1, const Vector2d& v2)
{
	// FIXME
	return false;
}

bool operator !=(const Vector2d& v1, const Vector2d& v2)
{
	// FIXME
	return false;
}

// overloaded I/O operators
std::ostream& operator <<(std::ostream& os, const Vector2d& v)
{
	// FIXME
	return os;
}

std::istream& operator >> (std::istream& is, Vector2d& v)
{
	// FIXME
	return is;
}


