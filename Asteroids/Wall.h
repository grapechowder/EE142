// Class to represent a hidden wall. These walls are placed outside the visible world for Asteroids and they
// enable us to get the wraparoud motion for the characters -- when a character moves outside the window,
// it re-appears on the other side (as if the window wraps around). Each wall has an offset vector --
// a value that can be added to a character's position to move it to the other side of the window.

#pragma once

#include <Thing.hpp>
#include <Vector2d.hpp>
#include <BoundingBox.hpp>

class Wall : public vmi::Thing
{
public:
	Wall(vmi::Vector2d _x, double width, double height, vmi::Vector2d _offset);
	~Wall();

	void handleCollision(const vmi::Thing *other);

	const vmi::Vector2d getOffset() const;

private:
	vmi::Vector2d offset;
};
