// Codes for handling the mouse buttons.
#pragma once
#ifndef VMI_GAME_MOUSE_H
#define VMI_GAME_MOUSE_H


#include "Graphics.hpp"

namespace vmi {

enum class MouseButton {
	Left = (int) sf::Mouse::Left,
	Right = sf::Mouse::Right,
	Middle = sf::Mouse::Middle
};

} // namespace vmi

#endif