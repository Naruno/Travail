#ifndef _UTILS_SDL_H_
#define _UTILS_SDL_H_

#define _CRT_SECURE_NO_WARNINGS

#include "../SDL-1.2.15/include/SDL.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Graphe_s Graphe;

struct Graphe_s {
	unsigned char nuance;
	Graphe *voisins[4];
};


int draw(SDL_Surface *p_window, SDL_Surface *p_image);
SDL_Surface * init(char * p_heightmapPath, SDL_Surface **p_heightmap, char * p_windowName);
int interaction(SDL_Event *p_e);
int update();
Graphe* InitGraphe(SDL_Surface *p_heightmap);
void _SDL_SetPixel(SDL_Surface* p_affichage, int p_x, int p_y, const Uint8 p_red, const Uint8 p_green, const Uint8 p_blue);

#endif