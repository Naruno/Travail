#ifndef FPSTIMER_H_INCLUDED
#define FPSTIMER_H_INCLUDED

//#define SDL_TIMER

#ifdef SDL_TIMER
#include <SDL/SDL.h>
    float fpsGetElapsed();
    float fpsGetDeltaTime();

#else
    // get elapsed time since init
    double fpsGetElapsed();

    // get elapsed time in seconds since last call of fpsStep()
    double fpsGetDeltaTime();
#endif

// get framerate
float fpsGetFPS();

// update (to be called once a frame)
void fpsStep();

// initialize the internal counters
void fpsInit();

#endif // FPSTIMER_H_INCLUDED
