// Class to represent a wall in the Pong game

#pragma once

#include <Thing.hpp>
#include <Vector2d.hpp>

class Wall :
	public vmi::Thing
{
public:
	Wall(const vmi::Vector2d& ul, const vmi::Vector2d& lr, const vmi::Vector2d& normal);
	~Wall();

	// handle collisions
	void handleCollision(const vmi::Thing* other);

	// Getter
	const vmi::Vector2d getNormal() const;

	

private:
	vmi::Vector2d n;				// normal vector pointing away from wall
};

