// Class for implementing delay timers. A timer can be created with a callback function, and the
// callback will be called in the future.

#ifndef VMI_GAME_TIMER_H
#define VMI_GAME_TIMER_H

#include <set>
#include <functional>

namespace vmi {

class Timer
{
public:
    static Timer* createTimer(double delayTime, const std::function<void (void)> callback);
    static Timer* createRepeatingTimer(double delayTime, const std::function<void (void)> callback);
    static void updateTimers(double dt);
    static void cancelAllTimers();

    void cancel() { timers.erase(this); }

private:
    Timer(double _delayTime, std::function<void (void)> _callback, bool _repeat)
        : timeRemaining(_delayTime), delayTime(_delayTime),
            repeat(_repeat), callback(_callback) { }

    double timeRemaining;           // remaining time for delay
    double delayTime;               // how long to delay
    bool repeat;                    // whether or not to repeat the delay

    std::function<void (void)> callback;     // function to call when timer expires

private:
    static inline std::set<Timer*> timers;

};

inline Timer* Timer::createTimer(double delayTime, std::function<void (void)> callback)
{
    // create the timer
    Timer* timer = new Timer(delayTime, callback, false);

    // add it to the set
    timers.insert(timer);

    return timer;
}

inline Timer* Timer::createRepeatingTimer(double delayTime, std::function<void (void)> callback)
{
    // create the timer
    Timer* timer = new Timer(delayTime, callback, true);

    // add it to the set
    timers.insert(timer);

    return timer;

}

// cancel all outstanding timers
inline void Timer::cancelAllTimers()
{
    timers.clear();
}


// Update timers, firing any callbacks as needed
inline void Timer::updateTimers(double dt)
{
    for (auto timer = timers.begin(); timer != timers.end(); /* intentionally blank */) {
        // update the timer
        (*timer)->timeRemaining -= dt;

        // has timer expired?
        if ((*timer)->timeRemaining <= 0) {
            // call the callback
            (*timer)->callback();

            // do we repeat?
            if ((*timer)->repeat) {
                // reset the timer
                (*timer)->timeRemaining = (*timer)->delayTime;
                ++timer;
            }
            else {
                // remove ourself
                timer = timers.erase(timer);
            }
        }
        else {
            ++timer;
        }
    }
}

} // namespace vmi

#endif