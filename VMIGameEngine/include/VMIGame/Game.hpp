// Abstract base class for game logic, including window creation and management.

#ifndef VMI_GAME_GAME_H
#define VMI_GAME_GAME_H


#include "Graphics.hpp"
#include <string>

#include "Vector2d.hpp"
#include "BoundingBox.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Color.hpp"
#include "Timer.hpp"
#include "Text.hpp"
#include "Thing.hpp"
#include "MovingThing.hpp"

namespace vmi {

class Game
{
// class functions
public:
    // Default constructor
    Game();
    
    // Constructor -- name and size of window
    Game(std::string name, int width, int height);
    
    // Plays the game -- this is our game loop
    void playGame();
    
    // Perform any per-frame updates. Called at end of each frame, after all
    // objects have been moved, but before the frame is
    // re-drawn. Each child class must supply an implementation of this
    virtual void update(double dt) = 0;
    
    // Returns true if game is over.
    virtual bool isOver() const { return false; }
    
    // Destructor
    virtual ~Game() {}
    
// Static functions
public:
    // Whether or not a key is pressed
    static bool isKeyPressed(Key key) { return sf::Keyboard::isKeyPressed( (sf::Keyboard::Key) key ); }
    
    // Whether mouse button is pressed
    static bool isMouseButtonPressed(MouseButton button) { return sf::Mouse::isButtonPressed( (sf::Mouse::Button) button ); }
    
    // Current location of mouse
    static const Vector2d mousePosition() {
        // get mouse position, convert to our Vector2d
        sf::Vector2i mPos = sf::Mouse::getPosition(*window);
        return Vector2d(mPos.x, mPos.y);
    }

	// Returns border of window
	static const BoundingBox getBounds();
    
    // Display a text message and wait for user keypress
    static Key createMessage(std::string msg, Vector2d position, int charSize = 60, Color color = Color::White);
    
// Class members
protected:
    std::string name;                   // name of game to display in window
    
    static inline sf::RenderWindow *window = nullptr;    // window for the game (needs to be static so we can get relative mouse position)
};


// Default constructor -- create a default window
inline Game::Game() : name("I forgot to name my window")
{
    // seed the random number generator
    srand((unsigned int) time(NULL));
    
    window = new sf::RenderWindow(sf::VideoMode(640, 400), name);
}

// Constructor -- name and size of window
inline Game::Game(std::string _name, int width, int height) : name(_name)
{
    // seed the random number generator
    srand((unsigned int) time(NULL));
    
	// Create the window
    window = new sf::RenderWindow(sf::VideoMode(width, height), name);
}

// Game loop
inline void Game::playGame()
{
    sf::Clock clock;            // clock for measuring frame time
    
    // game loop -- repeat until game ends or window is closed
    while (!isOver() && window->isOpen()) {
        // process any SFML events
        sf::Event ev;
        while (window->pollEvent(ev)) {
            // window closed?
            if (ev.type == sf::Event::Closed) {
                window->close();
            }
        }
        
        // measure frame time
        double dt = clock.restart().asSeconds();
        
        // make sure this stays sane
        dt = (dt > .04) ? .04 : dt;
        
        // update the timers
        Timer::updateTimers(dt);
        
        // move everyone
        MovingThing::moveAll(dt);
        
        // handle collisions between things
        MovingThing::handleCollisions();
        
        // update any game specific features
        update(dt);
        
        // remove all the dead things
        Thing::removeDeadThings();
        
        // draw everyone
        Thing::drawAll(*window);
    }
    
    // game is over, so delete the window
    delete window;

}


// Size of window
inline const BoundingBox Game::getBounds()
{
	if (window == nullptr) {
		// no window, so return empty bounds
		return BoundingBox();
	}
	else {
		return BoundingBox(Vector2d(), Vector2d(window->getSize().x, window->getSize().y));
	}
}


// Display a text message and wait for user keypress
inline Key Game::createMessage(std::string msgText, Vector2d position, int charSize, Color color)
{
    // display message
    Text msg(msgText, position);
    msg.setCharacterSize(charSize);
    msg.setFill(color);
    
    msg.draw(*window, sf::RenderStates::Default);
    window->display();
    
    // wait for a key press
    sf::Event event;
    Key key = Key::Space;
    bool gotKey = false;
    while (!gotKey && window->isOpen()) {
        while (window->pollEvent(event)) {
            // window closed?
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                gotKey = true;
                key = static_cast<Key>(event.key.code);
            }
        }
    }
    
    return key;
}

} // namespace vmi

#endif