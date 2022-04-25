#ifndef TIMER_H
#define TIMER_H
#include <SDL.h>

class Timer
{
    public:
        Timer();
        ~Timer();

        void start();
        void stop();
        void pause();
        void resume();

        Uint32 getTicks();

        bool isStarted();
        bool isPaused();

    private:
        Uint32 _startTicks;
        Uint32 _pauseTicks;
        bool _started;
        bool _paused;
};

#endif // TIMER_H
