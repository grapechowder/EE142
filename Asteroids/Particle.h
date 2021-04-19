// Class for a particle, which is the result of an explosion. The particles have a short
// lifetime, and they don't cause any collisions.

#pragma once

#include <MovingThing.hpp>
#include <Thing.hpp>
#include <Vector2d.hpp>
#include <Color.hpp>
#include <VertexShape.hpp>

class Particle : public vmi::MovingThing
{
public:
	Particle(vmi::Vector2d point, vmi::Vector2d v, vmi::Color color);
	Particle(vmi::Vector2d start, vmi::Vector2d end, vmi::Vector2d v, vmi::Color color);
	~Particle();

	void handleCollision(const vmi::Thing *other);

public:
	// make an explosion from a shape
	static void explode(const vmi::MovingThing *thing, bool lines = false);
};
