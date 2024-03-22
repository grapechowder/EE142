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
double Vector2d::dot(const Vector2d &v) const
{
	// FIXME
	return x*v.x + y * v.y;
}

// Vector magnitude
double Vector2d::magnitude() const
{
	// FIXME
	  
	 return sqrt((x * x) + (y * y));
}

// Nomralized vector
const Vector2d Vector2d::normalize() const
{
	// FIXME
	double mag = magnitude();

	if(mag == 0)
	{

		return Vector2d(0,0);
	}
	else
	{
	return Vector2d(x/mag, y/mag);
	}
	 
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
	x = _x;
}

void Vector2d::setY(double _y)
{
	// FIXME
	y = _y;
}

// overloaded operators -- assignment operators
Vector2d &Vector2d::operator+=(const Vector2d &rhs)
{
	// FIXME
	x += rhs.x;

	y += rhs.y;

	return *this;
}

Vector2d &Vector2d::operator-=(const Vector2d &rhs)
{
	// FIXME

	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vector2d &Vector2d::operator*=(double c)
{
	// FIXME
	x *= c;
	y *= c;

	return *this;
}

// overloaded operators -- arithmetic
const Vector2d operator+(Vector2d lhs, const Vector2d &rhs)
{
	// FIXME
	lhs += rhs;
	return lhs;
}

const Vector2d operator-(Vector2d lhs, const Vector2d &rhs)
{
	// FIXME
	

	lhs.y -= rhs.y;
	lhs.x -= rhs.x;

	return lhs;
}

const Vector2d operator*(Vector2d lhs, double rhs)
{
	// FIXME
	lhs *= rhs;
	return lhs;
}

const Vector2d operator*(double lhs, Vector2d rhs)
{
	// FIXME
	rhs *= lhs;
	return rhs;
}

const Vector2d Vector2d::operator-()
{
	// FIXME
	return Vector2d(-x, -y);
}

// overloaded operators -- comparisons
bool operator==(const Vector2d &v1, const Vector2d &v2)
{
	// FIXME
	if ((v1.y == v2.y) && (v1.x == v2.x))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator!=(const Vector2d &v1, const Vector2d &v2)
{
	// FIXME
	return !(v1 == v2);
}

// overloaded I/O operators
std::ostream &operator<<(std::ostream &os, const Vector2d &v)
{
	// FIXME
	os << "(" << v.x << ", " << v.y << ")";
	return os;
}

std::istream &operator>>(std::istream &is, Vector2d &v)
{
	// FIXME
	 is >> v.x >> v.y;

	return is;
}
