#include "sdl_stuff.h"
#include "decl.h"
#include <unistd.h>

SDL_Surface * bmpBalle;
SDL_Surface * screen;
SDL_Surface * bmpAttracteur;


typedef struct
{
    float x,y;
} vec2f;


extern void clicSouris(float x, float y);

vec2f ballePos = {0.0f,0.0f};
vec2f attractPos[NB_ATTRACTEURS];
int attractSetFlag[NB_ATTRACTEURS]= {0,0,0,0,0};


void sdl_setBallPosition(float x,float y)
{
    ballePos.x = x;
    ballePos.y = y;
}


void sdl_setAttracteurPosition(int index, float x,float y)
{
    attractPos[index].x = x;
    attractPos[index].y = y;

    attractSetFlag[index] = 1;
}

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
    bmpBalle = SDL_LoadBMP("balle.bmp");
    if (!bmpBalle)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 0;
    }
    SDL_SetColorKey(bmpBalle, SDL_SRCCOLORKEY, SDL_MapRGB(bmpBalle->format, 0, 0, 0));
    bmpAttracteur = SDL_LoadBMP("jupiter.bmp");
    if (!bmpAttracteur)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 0;
    }
    SDL_SetColorKey(bmpAttracteur, SDL_SRCCOLORKEY, SDL_MapRGB(bmpAttracteur->format, 0, 0, 0));

    return 1;
}



int sdl_loop( )
{
    int i;
    // message processing loop
    SDL_Event event;

    // clear screen
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

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

        case SDL_MOUSEBUTTONDOWN:
        {

            //Si le bouton gauche de la souris est presse
            if( event.button.button & SDL_BUTTON_LEFT )
            {
                // recuperation de la position du clic
                int x,y;
                SDL_GetMouseState(&x,&y);
                clicSouris((float)x/ WINDOW_SIZE, (float)(WINDOW_SIZE-y)/WINDOW_SIZE);
            }
            break;
        }

        } // end switch
    } // end of message processing

    // DRAWING STARTS HERE
    SDL_Rect dstrect;
    // Draw attracteur
    for(i = 0; i <NB_ATTRACTEURS; i++)
    {
        if(attractSetFlag[i])
        {
            dstrect.x =  WINDOW_SIZE*(attractPos[i].x) - bmpAttracteur->w/2;
            dstrect.y =  WINDOW_SIZE - WINDOW_SIZE*(attractPos[i].y) - bmpAttracteur->h/2;
            SDL_BlitSurface(bmpAttracteur, 0, screen, &dstrect);
        }

    }
    // position de la balle en pixels

    dstrect.x =  WINDOW_SIZE*(ballePos.x) - bmpBalle->w/2;
    dstrect.y =  WINDOW_SIZE - WINDOW_SIZE*(ballePos.y) - bmpBalle->h/2;
    SDL_BlitSurface(bmpBalle, 0, screen, &dstrect);

    // DRAWING ENDS HERE

    // finally, update the screen :)
    SDL_Flip(screen);

	usleep(1000);
		
    return 1;
}



void sdl_clean()
{
    // free loaded bitmap
    SDL_FreeSurface(bmpBalle);
    SDL_FreeSurface(bmpAttracteur);
    // all is well ;)
    printf("Exited cleanly\n");
}
