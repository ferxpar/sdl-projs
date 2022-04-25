#include "Timer.h"

Timer::Timer() : _startTicks(0), _pauseTicks(0), _started(false), _paused(false)
{
    //ctor
}

Timer::~Timer()
{
    //dtor
}

void Timer::start(){
    _startTicks = SDL_GetTicks();
    _pauseTicks = 0;
    _started = true;
    _paused = false;
}

void Timer::stop(){
    _startTicks = 0;
    _pauseTicks = 0;
    _started = false;
    _paused = false;
}

void Timer::pause(){

    if(_started && !_paused){
        _paused = true;
        _pauseTicks = SDL_GetTicks() - _startTicks;
        _startTicks = 0;
    }
}

void Timer::resume(){
    if(_started && _paused){
        _paused = false;
        _startTicks = SDL_GetTicks() - _pauseTicks;
        _pauseTicks = 0;
    }
}

Uint32 Timer::getTicks(){
    Uint32 time = 0;
    if(_started){
        if(_paused){
            time = _pauseTicks;
        } else {
            time = SDL_GetTicks() - _startTicks;
        }
    }
    return time;
}

bool Timer::isStarted(){
    return _started;
}
bool Timer::isPaused(){
    return _paused && _started;
}
