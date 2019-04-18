/**
 *	@file		gameSDL.h
 *
 *	@author		TEXIER Aur�lien
 *
 *	@version	1.0
 *
 *	@brief		Fichier g�rant l'application de l'algorithme A* dans un jeu d'innondation dans un graphe.
 *
 *	@details	Ce fichier d�clare les structures et fonctions utiles au d�veloppement de l'algorithme A* pour la r�solution du jeu d'innondation dans un graphe.
 */

#ifndef _ASTAR_H_
#define _ASTAR_H_

#include "game.h"

/**
*	@brief	Structure repr�sentant les listes utilis�es par l'algorithme A*.
*/
typedef struct sAStar
{
	int					m_g;			/**< Distance d�j� parcourue entre l'�tat initial et l'�tat courant.							*/
	int					m_f;			/**< Evaluation de la distance � parcourir entre l'�tat initial et l'�tat final (g + h).		*/
	board *				m_board;		/**< Plateau du jeu r�duit dans le noeud courant.												*/
	unsigned int		m_color;		/**< Derni�re couleur appliqu�e pour arriver � ce plateau.										*/
	struct sAStar *		m_prev;			/**< Pointeur vers le noeud correspondant au plateau pr�c�dent dans la solution.				*/
	struct sAStar *		m_next;			/**< Pointeur vers le noeud suivant (liste simplement chain�e)									*/
}aStar;

/**
*	@brief	Fonction permettant de cr�er (allouer) un noeud de liste utilis�e pour A*.
*
*	@param	p_board		Plateau r�duit du jeu.
*	@param	p_g			Distance d�j� parcourue entre l'�tat initial et l'�tat courant
*	@param	p_f			Evaluation de la distance � parcourir entre l'�tat initial et l'�tat final (g + h).
*	@param	p_color		Derni�re couleur appliqu�e pour arriver � ce plateau.
*	@param	p_prev		Pointeur vers le noeud correspondant au plateau pr�c�dent dans la solution.
*
*	@return	Le noeud de liste allou� et initialis�.
*/
aStar * CreateNodeAStar(board * p_board, int p_g, int p_f, unsigned int p_color, aStar * p_prev);

/**
*	@brief	Fonction permettant d'ins�rer un noeud dans un liste de mani�re tri�e ou non.
*
*	@param	p_list		Liste utilis�e pour A*.
*	@param	p_node		Noeud � ins�rer dans la liste.
*	@param	p_tri		1 si l'insertion doit se ffaire de mani�re tri�, 0 sinon.
*/
void InsertNodeAStar(aStar ** p_list, aStar * p_node, int p_tri);

/**
*	@brief	Fonction permettant de r�cup�rer la t�te d'une liste utilis�e pour A*.
*
*	@param	p_list		Pointeur sur la liste pour A*.
*
*	@return Pointeur sur le noeud de liste extrait.
*/
aStar * PopListAStar(aStar ** p_list);

/**
 *	@brief	Fonction permettant de savoir si un plateau se trouve dans une liste A*.
 *
 *	@param	p_list		Liste A*.
 *	@param	p_board		Plateau � chercher.
 *
 *	@return Noeud dans lequel on trouve le plateau pass� en param�tre (pointeur sur le pointeur dans la liste).
 */
aStar ** IsInList(aStar ** p_list, board * p_board);

/**
 *	@brief	Fonction de r�solution du jeu en utilisant l'algorithme A*.
 *
 *	@param	p_board				Plateau � r�soudre (plateau r�duit).
 *	@param	p_colors[OUT]		Tableau des couleurs de la solution.
 *	@param	p_nbColors[OUT]		Nombre de couleurs dans la solution.
 *
 *	@return	 1	si le plateau a �t� r�solu,
 *			-1	si une erreur est sruvenue,
 *			 0	sinon.
 */


int SolveGame(board * p_board, unsigned int ** p_colors, unsigned int * p_nbColors);
int comptage(aStar * list);
/**
*	@brief	Fonction de calcul de l'heuristique pour l'algorithme A*.
*
*	@param	p_board			Plateau du jeu.
*
*	@return	Valeur de l'heuristique.
*/
int H(board * p_board);

#endif
