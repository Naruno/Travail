#include "sdl_stuff.h"
#include <unistd.h>


SDL_Surface * bmp;
SDL_Surface * screen;

float x_pos = 0.0f;
float y_pos = 0.0f;

int sdl_startup()
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 0;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    screen = SDL_SetVideoMode(WINDOW_SIZE, WINDOW_SIZE, 32,
                              SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set  video: %s\n", SDL_GetError());
        return 0;
    }

    // load an image
    bmp = SDL_LoadBMP("balle.bmp");
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 0;
    }
    SDL_SetColorKey(bmp, SDL_SRCCOLORKEY, SDL_MapRGB(bmp->format, 0, 0, 0));

    return 1;
}


int sdl_loop()
{

    // message processing loop
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // check for messages
        switch (event.type)
        {
            // exit if the window is closed
        case SDL_QUIT:
            return 0;
            break;

            // check for keypresses
        case SDL_KEYDOWN:
        {
            // exit if ESCAPE is pressed
            if (event.key.keysym.sym == SDLK_ESCAPE)
                return 0;
            break;
        }
        } // end switch
    } // end of message processing

    // DRAWING STARTS HERE

    // clear screen
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

    // position de la balle en pixels
    SDL_Rect dstrect;
    dstrect.x =  WINDOW_SIZE*x_pos - bmp->w/2;
    dstrect.y =  WINDOW_SIZE - WINDOW_SIZE*y_pos - bmp->h/2;

    // draw bitmap
    SDL_BlitSurface(bmp, 0, screen, &dstrect);

    // DRAWING ENDS HERE

    // finally, update the screen :)
    SDL_Flip(screen);
	
	usleep(1000);

    return 1;
}


void sdl_setBallPosition(float x,float y)
{
    x_pos = x;
    y_pos = y;
}


void sdl_clean()
{
    // free loaded bitmap
    SDL_FreeSurface(bmp);

    // all is well ;)
    printf("Exited cleanly\n");
}
