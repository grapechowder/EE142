/*
 * Class to represent a 2-dimensional vector.
 */

#pragma once
#include <iostream>

class Vector2d
{
public:
	// Constructors
	Vector2d();
	Vector2d(double _x, double _y);

	// Dot product
	double dot(const Vector2d& v) const;

	// Vector magnitude
	double magnitude() const;

	// Nomralized vector
	const Vector2d normalize() const;

	// getters and setters
	double getX() const;
	double getY() const;
	void setX(double _x);
	void setY(double _y);

	// overloaded operators -- assignment operators
	Vector2d& operator+=(const Vector2d& rhs);
	Vector2d& operator-=(const Vector2d& rhs);
	Vector2d& operator*=(double c);

	// overloaded operators -- arithmetic
	friend const Vector2d operator +(Vector2d lhs, const Vector2d& rhs);	// addition
	friend const Vector2d operator -(Vector2d lhs, const Vector2d& rhs);	// subtraction
	friend const Vector2d operator *(Vector2d lhs, double rhs);				// vector*double
	friend const Vector2d operator *(double lhs, Vector2d rhs);				// double*vector
	const Vector2d operator-();												// unary minus

	// overloaded operators -- comparisons
	friend bool operator ==(const Vector2d& v1, const Vector2d& v2);			// equals
	friend bool operator !=(const Vector2d& v1, const Vector2d& v2);			// not equals

	// overloaded I/O operators
	friend std::ostream& operator <<(std::ostream& os, const Vector2d& v);		// output
	friend std::istream& operator >> (std::istream& is, Vector2d& v);			// input

private:
	double x;
	double y;
	double dx;
};

