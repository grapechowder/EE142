// Class for representing shapes as an array of vertices, connected by lines.
// Internally, we store the shape as a std::vector of SFML vertex arrays (which
// are a series of points connected with lines). By using a std::vector of these,
// we can build more complicated shapes -- each point doesn't need to be connected
// to the previous one. We can pick the pen up between segments when drawing.

#ifndef VMI_GAME_VERTEX_SHAPE_H
#define VMI_GAME_VERTEX_SHAPE_H

#include "Graphics.hpp"
#include <vector>

#include "Vector2d.hpp"
#include "Shape.hpp"
#include "BoundingBox.hpp"
#include "Color.hpp"

namespace vmi {

class VertexShape : public Shape
{
public:
    VertexShape() {}
    VertexShape(const VertexShape& other) : vertices(other.vertices), box(other.box) {}
    ~VertexShape() {}
    VertexShape& operator=(const VertexShape& rtSide) {
        // don't copy myself
        if (this != &rtSide) {
            vertices = rtSide.vertices;
            box = rtSide.box;
        }
    
        return *this;
    }
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // draw each vertex array
        for (auto it = vertices.begin(); it != vertices.end(); ++it) {
            target.draw(*it, states);
        }
    }
    
    const BoundingBox getBounds() const { return box; }
    
    void moveTo(const Vector2d& p, Color color = Color::White);
    void lineTo(const Vector2d& p, Color color = Color::White);
    
    // returns array of vertices for this shape
    std::vector<std::pair<Vector2d, Color>> getVertices() const;
    
private:
    std::vector<sf::VertexArray> vertices;
    BoundingBox box;
};

// Begin a new vertex array as part of this shape
inline void VertexShape::moveTo(const Vector2d& p, Color color)
{
    // add a new SFML vertex array
    sf::VertexArray va(sf::LinesStrip);
    
    // add this point to it
    va.append(sf::Vertex(sf::Vector2f((float) p.getX(), (float) p.getY()),
                         sf::Color(static_cast<sf::Uint32>(color))));
    
    // now add this vertex array to our list of them
    vertices.push_back(va);

    // and add this point to our bounding box
    box += p;
}

// Add a new point to our shape, drawing a line from the last point
inline void VertexShape::lineTo(const Vector2d& p, Color color)
{
    // if our list of vertex arrays is empty, then add a new one
    if (vertices.empty() ) {
        vertices.push_back(sf::VertexArray(sf::LinesStrip));
    }
    
    // add this new point to the current vertex array
    vertices.back().append(sf::Vertex(sf::Vector2f((float) p.getX(), (float) p.getY()),
                                      sf::Color(static_cast<sf::Uint32>(color))));
    
    // update our bounding box
    box += p;
}


// returns array of vertices for this shape
inline std::vector<std::pair<Vector2d, Color>> VertexShape::getVertices() const
{
    std::vector<std::pair<Vector2d, Color>> array;
    
    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        for (unsigned int i = 0; i < (*it).getVertexCount(); ++i) {
            array.push_back(std::make_pair( Vector2d((*it)[i].position.x, (*it)[i].position.y),
                                           (Color) ((*it)[i].color.toInteger())));
        }
    }
    
    return array;
}

} // namespace vmi

#endif