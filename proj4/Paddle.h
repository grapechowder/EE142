#pragma once

#include <Keyboard.hpp>
#include <MovingThing.hpp>
#include <Vector2d.hpp>

class Paddle : public vmi::MovingThing
{
public:
    Paddle(const vmi::Vector2d &position, const vmi::Vector2d &normal,
           vmi::Key up, vmi::Key down);
    //delete paddle
    ~Paddle();
    //move paddle
    void move(double dt);
    // Check for collision
    void handleCollision(const vmi::Thing *other);
    //return n
    const vmi::Vector2d getNormal() const;

private:
    vmi::Vector2d n;
    vmi::Key upKey;
    vmi::Key downKey;
    void bounce(const vmi::Vector2d& n);

    const double paddleSpeed = 400.0;
};