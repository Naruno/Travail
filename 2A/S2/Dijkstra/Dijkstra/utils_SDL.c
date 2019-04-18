#include "utils_SDL.h"

SDL_Surface * init(char * p_heightmapPath, SDL_Surface **p_heightmap, char * p_windowName)
{
	SDL_Surface *window;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("Error : %s\n", SDL_GetError());
		system("pause");
		return NULL;
	}

	*p_heightmap = SDL_LoadBMP(p_heightmapPath);
	window = SDL_SetVideoMode((*p_heightmap)->w, (*p_heightmap)->h, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
	if (!window)
	{
		printf("Error : %s\n", SDL_GetError());
		SDL_Quit();
		system("pause");
		return NULL;
	}

	SDL_WM_SetCaption(p_windowName, NULL);

	return window;
}

int interaction(SDL_Event *p_e)
{
	int quit = 0;

	while (SDL_PollEvent(p_e))
	{
		switch (p_e->type)
		{
			// Appuie sur la croix rouge de la fenêtre
			case SDL_QUIT:
				quit = 1;
				break;

			// Appuie sur une touche du clavier
			case SDL_KEYDOWN:
				switch (p_e->key.keysym.sym)
				{
					case SDLK_ESCAPE:
						quit = 1;
						break;

					default:
						break;
				}
				break;

			// Relachement d'une touche du clavier
			case SDL_KEYUP:
				switch (p_e->key.keysym.sym)
				{
					default:
						break;
				}
				break;

			// Appuie sur un bouton de la souris
			case SDL_MOUSEBUTTONDOWN:
				switch (p_e->button.button)
				{
					case SDL_BUTTON_LEFT:
						{

						}
						break;

					case SDL_BUTTON_RIGHT:
						break;

					case SDL_BUTTON_MIDDLE:
						break;

					default:
						break;
				}
				break;

			default:
				break;
		}
	}

	return quit;
}

int update()
{

}

Graphe* InitGraphe(SDL_Surface *p_heightmap) {
	int ha = p_heightmap->h , wi = p_heightmap->w, i;
	Graphe** graphe = (Graphe**)calloc(ha * wi, sizeof(Graphe*));
	for (i = 0; i < ha * wi; i++) {
		graphe[i] = (Graphe*)calloc(1, sizeof(Graphe));
	}
	
	for (i = 0; i < ha * wi; i++) {
		
		graphe[i]->nuance = ((unsigned char *)p_heightmap->pixels)[i];
		graphe[i]->voisins[0] = (i + 1 < wi) ? graphe[i + 1] : NULL;
		graphe[i]->voisins[1] = (i + wi < ha) ? graphe[i + wi] : NULL;
		graphe[i]->voisins[2] = (i - 1 >= 0) ? graphe[i - 1] : NULL;
		graphe[i]->voisins[3] = (i - wi >= 0) ? graphe[i - wi] : NULL;
	}
}

int draw(SDL_Surface *p_window, SDL_Surface *p_image)
{
	SDL_FillRect(p_window, NULL, SDL_MapRGBA(p_window->format, 0, 0, 0, 0));
	SDL_BlitSurface(p_image, NULL, p_window, NULL);

	SDL_Flip(p_window);

	return 0;
}


void _SDL_SetPixel(SDL_Surface* p_affichage, int p_x, int p_y, const Uint8 p_red, const Uint8 p_green, const Uint8 p_blue)
{
	Uint32 color = SDL_MapRGB(p_affichage->format, p_red, p_green, p_blue);

	// test si le pixel est dans la fenêtre avant de le dessiner si besoin
	if ((p_x >= 0 && p_x<p_affichage->clip_rect.w) && (p_y >= 0 && p_y<p_affichage->clip_rect.h)) 
		*((Uint32*)(p_affichage->pixels) + p_x + p_y * p_affichage->w) = color;
}