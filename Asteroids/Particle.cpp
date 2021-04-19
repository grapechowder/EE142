// Class for a particle, which is the result of an explosion. The particles have a short
// lifetime, and they don't cause any collisions. The particle is represented as a short line
// segment from start to end (if start and end are the same point, then particle appears as a dot)

#include <cstdlib>
#include <vector>

#include <MovingThing.hpp>
#include <Thing.hpp>
#include <Vector2d.hpp>
#include <Color.hpp>
#include <VertexShape.hpp>
#include <Timer.hpp>

#include "Particle.h"

using namespace vmi;

Particle::Particle(Vector2d point, Vector2d _v, Color color)
	: MovingThing(point, _v, Vector2d(), new VertexShape())
{
	// build the shape
	VertexShape *vs = dynamic_cast<VertexShape *>(shape);

	vs->moveTo(Vector2d(), color);
	vs->lineTo(Vector2d(1, 0), color);
	vs->lineTo(Vector2d(1, 1), color);
	vs->lineTo(Vector2d(0, 1), color);
	vs->lineTo(Vector2d(0, 0), color);

	// add some randomness to our velocity
	v += Vector2d(rand() % 200 - 100, rand() % 200 - 100);

	// die after 1 second
	Timer::createTimer(1.0, [&]() {
		die();
	});
}

Particle::Particle(Vector2d start, Vector2d end, Vector2d _v, Color color)
	: MovingThing(start, _v, Vector2d(), new VertexShape())
{
	// build the shape
	VertexShape *vs = dynamic_cast<VertexShape *>(shape);

	vs->moveTo(Vector2d(), color);
	vs->lineTo(end - start, color);

	// add some randomness to our velocity
	v += Vector2d(rand() % 200 - 100, rand() % 200 - 100);

	// spin a little bit
	w = rand() % 180 - 90; // between -90 and +90 angles / sec

	// die after 1 second
	Timer::createTimer(1.0, [&]() { die(); });
}

Particle::~Particle()
{
	delete shape;
}

void Particle::handleCollision(const Thing *other)
{
	// ignore all collisions
}

// Make an explosion from an array of vertices
void Particle::explode(const MovingThing *thing, bool lines)
{
	// get position, velocity, rotation, scale
	Vector2d x = thing->getPosition();
	Vector2d center = thing->getCenter() + x;
	double angle = thing->getRotation();
	double scale = thing->getScale();
	Vector2d v = thing->getVelocity();

	// build an SFML transform
	sf::Transform transform;
	transform.scale((float)scale, (float)scale, (float)center.getX(), (float)center.getY());
	transform.rotate((float)angle, (float)center.getX(), (float)center.getY());
	transform.translate((float)x.getX(), (float)x.getY());

	// get array of vertices that make up the shape
	const VertexShape *vs = dynamic_cast<const VertexShape *>(thing->getShape());
	auto vertices = vs->getVertices();

	// transform each vertex and make it a particle
	for (auto it = vertices.begin(); it != vertices.end(); ++it)
	{
		Vector2d point = (*it).first;
		Color color = (*it).second;

		// transform the point
		sf::Vector2f transformedPoint = transform.transformPoint((float)point.getX(), (float)point.getY());

		// make it a particle
		new Particle(Vector2d(transformedPoint.x, transformedPoint.y), v, color);
	}
}
