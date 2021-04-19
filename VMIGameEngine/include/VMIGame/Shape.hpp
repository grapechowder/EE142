// Abstract class for representing a shape
#pragma once
#ifndef VMI_GAME_SHAPE_H
#define VMI_GAME_SHAPE_H

#include "Graphics.hpp"
#include "BoundingBox.hpp"

namespace vmi {

class Shape
{
public:
    // Destructor
    virtual ~Shape() {};        // since destructor is empty, we're inlining it here
    
	// draw the shape
	virtual void draw(sf::RenderTarget& target,
		sf::RenderStates states) const = 0;

	// get a bounding box around the shape
	virtual const BoundingBox getBounds() const = 0;
};

} // namespace vmi

#endif