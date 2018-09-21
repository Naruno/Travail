#include "sdl_stuff.h"
#include "decl.h"

#include <unistd.h>

SDL_Surface * bmp;
SDL_Surface * screen;


typedef struct
{
    float x,y;
} vec2f;


vec2f positions[NB_BALLES];


extern void dragSouris(float x, float y);


int sdl_startup()
{
    int i;
    // reset positions
    for(i = 0; i<NB_BALLES; i++)
    {
        positions[i].x =0.0f;
        positions[i].y =0.0f;
    }

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
    int i;
    // message processing loop
    SDL_Event event;
    static int leftButtonState = 0; // 0 = released , 1 = pressed
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

        case SDL_MOUSEBUTTONUP:
        {
            //Si le bouton gauche de la souris est relache
            if( event.button.button & SDL_BUTTON_LEFT )
            {
                leftButtonState = 0;
            }
            break;

        }

        case SDL_MOUSEBUTTONDOWN:
        {

            //Si le bouton gauche de la souris est presse
            if( event.button.button & SDL_BUTTON_LEFT )
            {
                leftButtonState = 1;
            }
            break;
        }


        } // end switch
    } // end of message processing

    if(leftButtonState == 1)
    {
        int x,y;
        SDL_GetMouseState(&x,&y);
        dragSouris((float)x/ WINDOW_SIZE, (float)(WINDOW_SIZE-y)/WINDOW_SIZE);
    }

    // DRAWING STARTS HERE

    // clear screen
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

    // dessine les  balles
    for(i=0; i<NB_BALLES; i++)
    {
        // position de la balle en pixels
        SDL_Rect dstrect;
        dstrect.x =  WINDOW_SIZE*positions[i].x - bmp->w/2;
        dstrect.y =  WINDOW_SIZE - WINDOW_SIZE*positions[i].y - bmp->h/2;

        // draw bitmap
        SDL_BlitSurface(bmp, 0, screen, &dstrect);

    }

    // DRAWING ENDS HERE

    // finally, update the screen :)
    SDL_Flip(screen);
	
    usleep(1000);	

    return 1;
}


void sdl_setBallPosition(int balleIndex,float x,float y)
{

    positions[balleIndex].x = x;
    positions[balleIndex].y = y;
}


void sdl_clean()
{
    // free loaded bitmap
    SDL_FreeSurface(bmp);

    // all is well ;)
    printf("Exited cleanly\n");
}
