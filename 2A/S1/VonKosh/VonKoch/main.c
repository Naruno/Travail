#include <stdio.h>
#include <stdlib.h>
#include "utils_SDL.h"
#include "vecteur.h"
#include <windows.h>

/**
*	@brief	Fonction permettant de dessiner une courbe de Koch.
*
*	@param	p_affichage		Fenêtre sur laquelle on souhaite dessiner.
*	@param	p_iteration		Nombre d'itération que l'on souhaite appliquer à la courbe.
*	@param	p_a				Point de départ du segment.
*	@param	p_b				Point d'arrivée du segment.
*/
void vonKoch(SDL_Surface * p_affichage, int p_iteration, point p_a, point p_b)
{	
	point p1, p2, p3;
	//decoupage(p_a, p_b, &p1, &p3);

	p2 = nouveau_vect(p_a, p_b);
	

	if (!p_iteration) {

		tracer(p_affichage, p_b, p_a);
		
		tracer(p_affichage, p_a, p2);
		
		tracer(p_affichage, p2, p_b);
		
	
	}
	else {
		

		vonKoch(p_affichage, p_iteration -1 , p_a, p2);
		vonKoch(p_affichage, p_iteration -1 , p2, p_b);
		vonKoch(p_affichage, p_iteration -1 , p_b, p_a);
	
	}			
}

int main(int argc, char **argv)
{
	point a, b;
	SDL_Surface * window;
	int iterations = 1;
	int quit = 0;
	enum { dessin1, dessin2, rendu } state = dessin1;
	SDL_Event e;
	Uint8 mouseButton;
	point mousePos;


	// Initialisation
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "ERREUR - SDL_Init\n>>> %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	// Permet de quitter proprement par la suite (revenir à la résolution initiale de l'écran avec le bon format vidéo)
	atexit(SDL_Quit);
	// Initialise le mode vidéo de la fenêtre
	window = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	// Si on n'a pas réussi à créer la fenêtre on retourne une erreur
	if (window == NULL) {
		fprintf(stderr, "ERREUR - impossible de passer en : %dx%dx%d\n>>> %s\n", 640, 480, 32, SDL_GetError());
		exit(EXIT_FAILURE);
	}

	// On met le titre sur la fenêtre
	SDL_WM_SetCaption("VonKoch", NULL);

	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				quit = 1;
				break;
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_ESCAPE)
					quit = 1;
				if (e.key.keysym.sym == SDLK_KP_PLUS)
					iterations++;
				if (e.key.keysym.sym == SDLK_KP_MINUS)
				{
					iterations--;
					iterations = iterations >= 0 ? iterations : 0;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouseButton = SDL_GetMouseState(&mousePos.m_x, &mousePos.m_y);

				switch (state)
				{
				case dessin1:
					a.m_x = mousePos.m_x;
					a.m_y = mousePos.m_y;
					state = dessin2;
					break;
				case dessin2:
					b.m_x = mousePos.m_x;
					b.m_y = mousePos.m_y;
					state = rendu;
					break;
				case rendu:
				default:
					a.m_x = mousePos.m_x;
					a.m_y = mousePos.m_y;
					state = dessin2;
					iterations = 0;
					break;
				}
				break;
			}
		}
		if (state == rendu)
		{
			// On vide la fenêtre (on la remplit en noir)
			SDL_FillRect(window, &(window->clip_rect), SDL_MapRGB(window->format, 0, 0, 0));

			vonKoch(window, iterations, a, b);

			// Met à jour le buffer de la fenêtre
			SDL_UpdateRect(window, 0, 0, 0, 0);
			// Flip le buffer pour l'envoyer vers l'écran (la fenêtre est configurée en double buffer)
			SDL_Flip(window);
		}
	}
	return EXIT_SUCCESS;
}