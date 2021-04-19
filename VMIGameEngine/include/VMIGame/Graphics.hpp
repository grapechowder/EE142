#pragma once
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
#include <cstring>
#include <fstream>

namespace sf
{
	typedef std::string String;
	typedef unsigned int Uint32;

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
		Time restart()
		{
			return Time();
		}
	};

	class Vector2f
	{
	public:
		Vector2f() :x(0), y(0) {}
		Vector2f(float _x, float _y) : x(_x), y(_y) {}

		float x;
		float y;
	};

	class Vector2i
	{
	public:
		Vector2i() {}
		Vector2i(int _x, int _y) : x(_x), y(_y) {}

		int x;
		int y;
	};

	class FloatRect
	{
	public:
		FloatRect() : left(0), top(0), width(30), height(20) {}
		FloatRect(float _l, float _t, float _w, float _h) : left(_l), top(_t), width(_w), height(_h) {}

		float left;
		float top;
		float width;
		float height;
	};

	class Transform
	{
	public:
		Transform() : x(0), y(0) {}
		Transform& translate(float _x, float _y)
		{
			x = _x;
			y = _y;
			return *this;
		}
		Transform& scale(float scaleX, float scaleY, float x, float y) { return *this; }
		Transform& scale(float scaleX, float scaleY) { return *this; }
		Transform& rotate(float angle, float x, float y) { return *this; }
		sf::FloatRect transformRect(sf::FloatRect rect)
		{
			return sf::FloatRect(rect.left + x, rect.top + y, rect.width, rect.height);
		}
		sf::Vector2f transformPoint(float x, float y) { return sf::Vector2f(x, y); }

		float x;
		float y;
	};

	class Color
	{
	public:
		Color() {}
		Color(Uint32 c) {}
		Uint32 toInteger() const { return 0; }
	};

	class Font
	{
	public:
		Font() {}
		bool loadFromFile(const std::string &filename)
		{
			return true;
		}
	};

	class Texture
	{
	public:
		Texture() {}
		bool loadFromFile(std::string filename)
		{
			size_t last = filename.find_last_of("/\\");
			if (last != std::string::npos)
				filename = filename.substr(last + 1);

			std::ifstream is(filename, std::ifstream::in | std::ifstream::binary);
			if (is)
			{
				unsigned char buffer[256];
				is.read((char *)buffer, 256);
				is.close();

				// find size of file
				unsigned int i = 0;
				while (i < 256 && strncmp((char *)&(buffer[i]), "IHDR", 4) != 0)
					i++;
				if (i >= 256)
					return false;

				unsigned int w = ((unsigned int)buffer[i + 4] << 24) | ((unsigned int)buffer[i + 5] << 16) | ((unsigned int)buffer[i + 6] << 8) | (unsigned int)buffer[i + 7];
				unsigned int h = ((unsigned int)buffer[i + 8] << 24) | ((unsigned int)buffer[i + 9] << 16) | ((unsigned int)buffer[i + 10] << 8) | (unsigned int)buffer[i + 11];

				size = Vector2i(w, h);
				return true;
			}
			else
				return false;
		}

		Vector2i size;
	};
	class Shape
	{
	public:
		Shape() {}
		void setPosition(float x, float y) {}
		void setFillColor(const sf::Color &color) {}
		void setOutlineColor(const sf::Color &color) {}
	};

	class RectangleShape : public Shape
	{
	public:
		RectangleShape() {}
		void setSize(sf::Vector2f v) {}
	};

	class ConvexShape : public Shape
	{
	public:
		ConvexShape() {}
		void setPointCount(int count) {}
		void setPoint(int i, const Vector2f &v) {}
	};

	class Text : public Shape
	{
	public:
		Text() {}
		void setFont(sf::Font font) {}
		void setString(std::string str) {}
		void setCharacterSize(int newSize) {}
		void setFillColor(sf::Color color) {}
		void setOutlineColor(sf::Color color) {}
	};

	class Vertex
	{
	public:
		Vertex() {}
		Vertex(const sf::Vector2f &_position, const sf::Color &_color) : position(_position), color(_color) {}

		sf::Vector2f position;
		sf::Color color;
	};

	enum PrimitiveType
	{
		LinesStrip
	};

	class VertexArray : public Shape
	{
	public:
		VertexArray(sf::PrimitiveType type) {}
		void append(sf::Vertex v) {}
		unsigned int getVertexCount() const { return 0; }
		const sf::Vertex &operator[](std::size_t idx) const { return array[0]; }

	private:
		sf::Vertex array[1];
	};

	class VideoMode
	{
	public:
		VideoMode(int _w, int _h) : w(_w), h(_h) {}

		int w;
		int h;
	};
	class Keyboard
	{
	public:
		enum Key
		{
			Unknown = -1,
			A = 0,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,
			Num0,
			Num1,
			Num2,
			Num3,
			Num4,
			Num5,
			Num6,
			Num7,
			Num8,
			Num9,
			Escape,
			LControl,
			LShift,
			LAlt,
			LSystem,
			RControl,
			RShift,
			RAlt,
			RSystem,
			Menu,
			LBracket,
			RBracket,
			SemiColon,
			Comma,
			Period,
			Quote,
			Slash,
			BackSlash,
			Tilde,
			Equal,
			Dash,
			Space,
			Return,
			BackSpace,
			Tab,
			PageUp,
			PageDown,
			End,
			Home,
			Insert,
			Delete,
			Add,
			Subtract,
			Multiply,
			Divide,
			Left,
			Right,
			Up,
			Down,
			Numpad0,
			Numpad1,
			Numpad2,
			Numpad3,
			Numpad4,
			Numpad5,
			Numpad6,
			Numpad7,
			Numpad8,
			Numpad9,
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			F13,
			F14,
			F15,
			Pause,
			KeyCount
		};

		// For testing on zyBooks, use a static global to control keypress
		static inline bool keyIsPressed = false;
		static bool isKeyPressed(Key key) { return keyIsPressed; }
	};

	class Event
	{
	public:
		Event() {}
		enum EventType
		{
			Closed,
			KeyPressed
		};
		struct KeyEvent
		{
			Keyboard::Key code;
		};

		EventType type;
		KeyEvent key;
	};

	class RenderStates
	{
	public:
		RenderStates() {}

		sf::Transform transform;

		static const RenderStates Default;
	};

	inline const sf::RenderStates sf::RenderStates::Default;

	class RenderTarget
	{
	public:
		RenderTarget() {}
		void draw(sf::Shape shape, sf::RenderStates states = sf::RenderStates::Default) {}
		void draw(sf::Shape shape) {}
		void clear() {}
	};

	class RenderWindow : public RenderTarget
	{
	public:
		RenderWindow(sf::VideoMode mode, const String &title) {}
		bool isOpen() { return true; }
		void close() {}
		void display() {}
		bool pollEvent(sf::Event event) { return false; }
		Vector2i getSize() { return Vector2i(640, 480); }
	};

	class Sprite : public Shape
	{
	public:
		sf::FloatRect getLocalBounds() const
		{
			return sf::FloatRect(0, 0, texture.size.x, texture.size.y);
			//			return sf::FloatRect(0, 0, 10, 10);
		}
		void setTexture(sf::Texture _texture) { texture = _texture; }
		void draw(sf::RenderTarget &target, RenderStates states) {}

		sf::Texture texture;
	};

	class Mouse
	{
	public:
		enum Button
		{
			Left,
			Right,
			Middle
		};
		static bool isButtonPressed(sf::Mouse::Button button) { return false; }
		static Vector2i getPosition(sf::RenderWindow window) { return Vector2i(); }
	};
} // namespace sf

#endif

#endif