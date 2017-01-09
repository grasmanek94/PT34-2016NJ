#include "Timer.hpp"
#include <Arduino.h>


Timer::Timer(unsigned long interval, bool autoReset)
    : _interval(interval), _autoReset(autoReset), _running(false)
{

}

Timer::~Timer()
{

}

void Timer::start()
{
    reset();
    _running = true;
}

void Timer::stop()
{
    _running = false;
}

void Timer::reset()
{
    _deadline = millis() + _interval;
}

bool Timer::isRunning()
{
    return _running;
}

bool Timer::isElapsed()
{
    if(millis() >= _deadline)
    {
        if(_autoReset)
        {
            start();
        }
        else
        {
            stop();
        }
        return true;
    }
    return false;
}

void Timer::setInterval(unsigned long interval)
{
    _interval = interval;
}

unsigned long Timer::getInterval()
{
    return _interval;
}

void Timer::setAutoReset(bool value)
{
    _autoReset = value;
}

bool Timer::getAutoReset()
{
    return _autoReset;
}
