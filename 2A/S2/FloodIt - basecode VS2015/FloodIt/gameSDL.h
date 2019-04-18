/**
 *	@file		gameSDL.h
 *
 *	@author		TEXIER Aur�lien
 *
 *	@version	1.0
 *
 *	@brief		Fichier g�rant un jeu d'innondation dans un graphe en SDL.
 *
 *	@details	Ce fichier d�clare les structures et fonctions utiles � la gestion de la SDL pour cr�er un jeu d'innondation dans un graphe.
 */

#ifndef _GAME_SDL_H_
#define _GAME_SDL_H_

#include "game.h"
#include "SDL\SDL.h"

/**
*	@brief	Structure repr�sentant le jeu en SDL.
*/
typedef struct sGameSDL
{
	game *			m_game;			/**< Jeu. @see game.													*/

	int				m_res;			/**< R�solution des cases du jeu.										*/
	SDL_Surface	*	m_pWindow;		/**< Fen�tre SDL permettant l'affichage du jeu.							*/
}gameSDL;

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
gameSDL * CreateGameSDL(unsigned char p_size, int p_res, int p_nbColor);

/**
 *	@brief	Fonction permettant de recharger le jeu en SDL.
 *			(Attention aux fuites m�moires)
 *
 *	@param	p_gameSDL	Jeu en SDL.
 */
void ReloadGameSDL(gameSDL ** p_gameSDL);

/**
*	@brief	Fonction permettant de "dessiner" le jeu en SDL.
*
*	@param	p_gameSDL	Jeu en SDL.
*/
void DrawGameSDL(gameSDL * p_gameSDL);

/**
*	@brief Fonction permettant de lib�rer le jeu SDL.
*
*	@param	p_game		Jeu SDL � d�sallouer.
*/
void FreeGameSDL(gameSDL * p_gameSDL);

#endif
