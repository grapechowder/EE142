// Text that can be drawn to a window
#pragma once
#ifndef VMI_GAME_TEXT_H
#define VMI_GAME_TEXT_H

#include "Graphics.hpp"
#include <string>
#include <cstdlib>

#include "Vector2d.hpp"
#include "Color.hpp"

namespace vmi {

class Text
{
public:
    Text() {
        loadDefaultFont();
        shape.setFont(*font);
    }
    Text(std::string _text, Vector2d _position) : text(_text), position(_position) {
        loadDefaultFont();
        shape.setFont(*font);
        shape.setString(text);
    }
    ~Text() {}

    // draw the text
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        sf::Transform transform;
        transform.translate((float)position.getX(), (float) position.getY());
        states.transform = transform;
        target.draw(shape, states);
    }

    // setters
    void setText(std::string newText) {
        text = newText;
        shape.setString(text);
    }
    void setCharacterSize(unsigned int newSize) {
        characterSize = newSize;
        shape.setCharacterSize(characterSize);
    }
    void setPosition(const Vector2d newPosition) { position = newPosition; }
    void setFill(const Color newColor) {
        fillColor = newColor;
        shape.setFillColor(sf::Color(static_cast<sf::Uint32>(fillColor)));
    }
    void setOutline(const Color newColor) {
        outlineColor = newColor;
        shape.setOutlineColor(sf::Color(static_cast<sf::Uint32>(outlineColor)));
    }

private:
    std::string text;               // text that is displayed
    unsigned int characterSize;     // size of characters
    Vector2d position;              // location in window
    Color fillColor;                // color used to fill the text
    Color outlineColor;             // color used to outline the text

    sf::Text shape;                 // SFML shape

    void loadDefaultFont() {
#ifndef ZYBOOKS        
        if (font == nullptr) {
            font = new sf::Font();

            char* path;
            bool success = false;

            // didn't find one, so hope it's in the right dir
            font->loadFromFile("./VMIGameEngine/resource/sansation.ttf");
        }
#endif        
    }

    static inline sf::Font *font = nullptr;
};

} // namespace vmi

#endif