#include "gameSDL.h"

/**
 *	@brief	Fonction permettant de cr�er le jeu en SDL.
 *			La fonction cr�e la fen�tre SDL.
 *
 *	@param	p_size		Taille du plateau.
 *	@param	p_res		R�solution des cases du jeu.
 *	@param	p_nbColor	Nombre de couleur utiliser pour la partie.
 *
 *	@return	Le jeu SDL.
 */
gameSDL * CreateGameSDL(unsigned char p_size, int p_res, int p_nbColor){
	gameSDL * result;
	// On alloue la m�moire.
	result = (gameSDL*)malloc(sizeof(gameSDL));
	
	result->m_res = p_res;

	// On cr�e le jeu.
	result->m_game = CreateGame(p_size, p_nbColor);

	// On cr�e la fen�tre SDL.
	result->m_pWindow = SDL_SetVideoMode(p_size*p_res, p_size*p_res, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
	SDL_WM_SetCaption("Flood-it", "Flood-it !!!");
	SDL_WM_SetIcon(NULL, NULL);

	return result;
}

/**
 *	@brief	Fonction permettant de recharger le jeu en SDL.
 *			(Attention aux fuites m�moires)
 *
 *	@param	p_gameSDL	Jeu en SDL.
 */
void ReloadGameSDL(gameSDL ** p_gameSDL){
	unsigned char size = 0, nbColor = 0;
	// Test pour v�rifier que les donn�es en param�tres sont valides.
	if (!p_gameSDL || !(*p_gameSDL))	return;
	// Si un jeu existe d�j�.
	if ((*p_gameSDL)->m_game){
		// On conserve les donn�es du jeu pr�c�dent.
		nbColor = (*p_gameSDL)->m_game->m_nbColor;
		size = (*p_gameSDL)->m_game->m_size;

		// Puis on lib�re ce jeu.
		FreeGame((*p_gameSDL)->m_game);
	}
	// On cr�e un nouveau jeu.
	(*p_gameSDL)->m_game = CreateGame(size, nbColor);
}

/**
 *	@brief	Fonction permettant de "dessiner" le jeu en SDL.
 *
 *	@param	p_gameSDL	Jeu en SDL.
 */
void DrawGameSDL(gameSDL * p_gameSDL){
	// Element qui vas nous servir � nous d�placer dans la fen�tre pour dessiner.
	SDL_Rect rect;
	int i, j;

	SDL_Surface *ecran = p_gameSDL->m_pWindow;	
	// Mise � jour de l'�cran avec sa nouvelle couleur.
	SDL_Flip(ecran);
	rect.w = p_gameSDL->m_res;
	rect.h = p_gameSDL->m_res;
	rect.x = 0;
	rect.y = 0;

	// Test pour v�rifier que les donn�es en param�tres sont valides.
	if (!p_gameSDL || !p_gameSDL->m_pWindow || !p_gameSDL->m_game || !p_gameSDL->m_game->m_board)	return;


	// On dessine le plateau case par case.
	for (i = 0; i < p_gameSDL->m_game->m_size; i++){
		rect.x = 0;
		for (j = 0; j < p_gameSDL->m_game->m_size; j++){
			int index = j + (p_gameSDL->m_game->m_size)*i;
			color couleur = p_gameSDL->m_game->m_colors[p_gameSDL->m_game->m_board->m_graph[index]->m_colorIndex];
			SDL_FillRect(p_gameSDL->m_pWindow, &rect, SDL_MapRGB(p_gameSDL->m_pWindow->format, couleur.r, couleur.g, couleur.b));

			rect.x += p_gameSDL->m_res;
		}
		rect.y += p_gameSDL->m_res;
	}
	// On met � jour la fen�tre compl�te.
	SDL_UpdateRect(p_gameSDL->m_pWindow, 0, 0, 0, 0);
}

/**
 *	@brief Fonction permettant de lib�rer le jeu SDL.
 *
 *	@param	p_game		Jeu SDL � d�sallouer.
 */
void FreeGameSDL(gameSDL * p_gameSDL){
	// Test pour v�rifier que les donn�es en param�tres sont valides.
	if (!p_gameSDL)	return;

	// On lib�re la fen�tre SDL.
	if (p_gameSDL->m_pWindow) SDL_FreeSurface(p_gameSDL->m_pWindow);

	// On lib�re le jeu.
	if (p_gameSDL->m_game)	FreeGame(p_gameSDL->m_game);

	// On lib�re finalement le jeu SDL.
	free(p_gameSDL);
}
