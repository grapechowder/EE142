// enum for specifying colors
#pragma once
#ifndef VMI_GAME_COLOR_H
#define VMI_GAME_COLOR_H

namespace vmi {

enum class Color : unsigned int
{
	Black = 0x000000ff,
	White = 0xffffffff,
	Red = 0xff0000ff,
	Green = 0x00ff00ff,
	Blue = 0x0000ffff,
	Yellow = 0xffff00ff,
	Magenta = 0xff00ffff,
	Cyan = 0x00ffffff,
	Transparent = 0x00000000
};

} // namespace vmi

#endif