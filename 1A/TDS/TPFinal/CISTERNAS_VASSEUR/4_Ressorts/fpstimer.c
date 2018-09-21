#include "fpstimer.h"


#ifdef WIN32
// windows
#include <windows.h>
#define WIN32_LEAN_AND_MEAN

#else
// linux
#include <time.h>
#endif


#ifdef SDL_TIMER
    // SDL Tick fashion
    // milliseconds
    unsigned int gAppInit = 0;
    unsigned int gLast = 0;
    unsigned int gDelta = 0;


    // get elapsed time since init (in seconds)
    float fpsGetElapsed()
    {
        return (float) (gLast - gAppInit)/1000.0f;
    }

    // get framerate (hz)
    float fpsGetFPS()
    {
        return  1000.0f/(float)gDelta;
    }

    // get elapsed time in seconds since last call of fpsStep()
    float fpsGetDeltaTime()
    {
        float ret = (float)gDelta/1000.0f;
        // prevent unstabilities
        if(ret>0.05f)
            ret = 0.1f;
        return ret;
    }

    // update (to be call at each frame)
    void fpsStep()
    {
        unsigned int temp = SDL_GetTicks();
        gDelta = temp - gLast;
        gLast = temp;

    }

    // initialize
    void fpsInit()
    {
        gAppInit = SDL_GetTicks();
        gLast = gAppInit ;
        return ;
    }


#else
    //---------------------------
    //   static vars
    #ifdef WIN32
    // windows

    // ------------
    // Windows version ( with performance counters)
    static LARGE_INTEGER gLast;
    static LARGE_INTEGER gRes;
    static LARGE_INTEGER gAppInit;

    #else
    // linux
    // see article http://www.kerrywong.com/2009/05/28/timing-methods-in-c-under-linux/
    // all in ticks
    static struct timespec gRes ;
    static struct timespec gAppInit ;
    static struct timespec gLast ;

    #endif


    double gDelta = 0.0;
    double elfromstart = 0.0;

    // get elapsed time since init (in seconds)
    double fpsGetElapsed()
    {
        return elfromstart ;
    }

    // get framerate (hz)
    float fpsGetFPS()
    {
        return  1.0f/(float)gDelta;
    }

    // get elapsed time in seconds since last call of fpsStep()
    double fpsGetDeltaTime()
    {
            // here is a patch to prevent big dt when dragging the window (could make the physic simulation explode)
            // we make the assumption the a delta over 100 ms (=10fps) is not aceptable
            if(gDelta>0.10)
                    return 0.1;
        return gDelta;
    }

    // update (to be call at each frame)
    void fpsStep()
    {
    #ifdef WIN32
    // windows
        LARGE_INTEGER temp;
        QueryPerformanceCounter(&temp);
        gDelta =  (double)(temp.QuadPart - gLast.QuadPart) /( double)gRes.QuadPart;
        elfromstart =  (double)(temp.QuadPart - gAppInit.QuadPart) /( double)gRes.QuadPart;
    #else
    // linux
        struct timespec temp ;
        clock_gettime(CLOCK_REALTIME, &temp);
        gDelta =  (temp.tv_sec - gLast.tv_sec)  + (double) (temp.tv_nsec - gLast.tv_nsec) / 1000000000.0 ;
        elfromstart =  (temp.tv_sec - gAppInit.tv_sec)  + (float) (temp.tv_nsec - gAppInit.tv_nsec) / 1000000000.0 ;
    #endif
        gLast = temp;
    }


    // initialize
    void fpsInit()
    {

    #ifdef WIN32
    // windows
        QueryPerformanceFrequency(&gRes);
        QueryPerformanceCounter(&gAppInit);

    #else
    // linux
        clock_getres(CLOCK_REALTIME, &gRes);
        clock_gettime(CLOCK_REALTIME, &gAppInit);
    #endif

        gDelta = 0.0;
        gLast = gAppInit ;
        return ;
    }

#endif





