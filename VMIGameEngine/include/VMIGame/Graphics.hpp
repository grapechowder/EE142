#ifndef VMI_GAME_GRAPHICS_H
#define VMI_GAME_GRAPHICS_H

/*
* This header file simply serves as a wrapper around the SFML library. It is included so that we can
* perform unit testing on the code with gcc for the zyBooks environment.
*
* DO NOT MODIFY THIS FILE!
*/

#ifndef ZYBOOKS

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#else
// This is for non-Visual Studio systems where the SFML library has not been installed

#include <string>

namespace sf
{
	typedef std::string String;

	class Time
	{
	public:
		Time() {}
		float asSeconds() const { return 0; }
	};

	class Clock
	{
	public:
		Clock() {}
		Time restart() {
			return Time();
		}
	};

	class Vector2f
	{
	public:
		Vector2f() { }
		Vector2f(float _x, float _y) : x(_x), y(_y) { }
	private:
		float x;
		float y;
	};

	class Transform
	{
	public:
		Transform() { }
		void translate(float x, float y) { }
	};

	class Color
	{
	public:
		Color() { }

	};

	class Shape
	{
	public:
		Shape() {}
		void setPosition(float x, float y) { }
		void setFillColor(const sf::Color& color) { }
	};

	class RectangleShape : public Shape
	{
	public:
		RectangleShape() {}
		void setSize(sf::Vector2f v) {}
	};

	class VideoMode
	{
	public:
		VideoMode(int w, int h) { }
	};

	class Event
	{
	public:
		Event() { }
		enum EventType {
			Closed
		};
		EventType type;
	};

	class RenderStates
	{
	public:
		RenderStates() {}

	};
	
	class RenderTarget
	{
	public:
		RenderTarget() { }
		void draw(sf::Shape shape, sf::Transform transform) { }
		void draw(sf::Shape shape) { }
		void clear() { }
	};

	class RenderWindow : public RenderTarget
	{
	public:
		RenderWindow(sf::VideoMode mode, const String& title) { }
		bool isOpen() { return true; }
		void close() { }
		void display() { }
		bool pollEvent(sf::Event event) { return false; }
	};

	class Keyboard
	{
	public:
		enum Key {
			S, W, Up, Down
		};

		// For testing on zyBooks, return true for S and Up, false for W and Down
		static bool isKeyPressed(Key key) { return (key == Key::S || key == Key::Up); }
	};

}

#endif

#endif