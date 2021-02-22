// Class for working with sprite-based shapes

#ifndef VMI_GAME_SPRITE_SHAPE_H
#define VMI_GAME_SPRITE_SHAPE_H

#include <map>
#include <string>
#include "Graphics.hpp"

#include "BoundingBox.hpp"
#include "Shape.hpp"

namespace vmi {

class SpriteShape : public Shape
{
public:
    SpriteShape() : Shape(), texture(nullptr) {}
    SpriteShape(std::string filename);
    SpriteShape(const SpriteShape& other);
    SpriteShape& operator=(const SpriteShape& rtSide);
    ~SpriteShape() {}
    
    // draw the sprite
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(sprite, states);
    }
    
    // get a bounding box around the shape
    const BoundingBox getBounds() const {
        // get SFML's representation of the bounds
        sf::FloatRect box = sprite.getLocalBounds();
    
        // turn it into our bounding box
        return BoundingBox(Vector2d(box.left, box.top), 
                Vector2d(box.left+box.width, box.top+box.height));
    }
   
    
private:
    sf::Sprite sprite;          // SFML sprite
    sf::Texture *texture;       // texture to use for sprite
    
    
    // map of all textures, indexed by filename
    static inline std::map<std::string, sf::Texture*> textures;
};

// Constructor
// Input: filename = name of texture file
inline SpriteShape::SpriteShape(std::string filename) : Shape()
{
    // look to see if texture has already been loaded
    auto it = textures.find(filename);
    if (it != textures.end()) {
        // texture was already loaded, so just re-use it
        texture = it->second;
    }
    else {
        // need to load texture and store it in map
        texture = new sf::Texture();
        if (texture->loadFromFile(filename)) {
            // add it to the map
            textures.insert( std::pair<std::string, sf::Texture*>(filename, texture));
        }
        else {
            // couldn't load texture file, so un-do everything
            delete texture;
            texture = nullptr;
        }
    }
    
    // now initialize the SFML Sprite
    if (texture != nullptr) {
        sprite.setTexture(*texture);
    }
    
}

// Copy constructor
inline SpriteShape::SpriteShape(const SpriteShape& other)
{
    texture = other.texture;
    
    // set the texture for my sprite
    if (texture != nullptr) {
        sprite.setTexture(*texture);
    }
}

// Assignment operator
inline SpriteShape& SpriteShape::operator=(const SpriteShape& rtSide)
{
    // make sure this isn't me
    if (this != &rtSide) {
        // copy his texture
        texture = rtSide.texture;
        
        // set the texture for my sprite
        if (texture != nullptr) {
            sprite.setTexture(*texture);
        }
    }
    
    return *this;
}

} // namespace vmi

#endif