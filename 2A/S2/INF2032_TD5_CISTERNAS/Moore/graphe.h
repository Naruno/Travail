#ifndef GRAPHE_H_
#define GRAPHE_H_

#include "tools.h"

#define ATTRIBUT_SPECIAL	2


typedef int ATTRIBUT;

/* Structure d'arc */
typedef struct {
	ATTRIBUT value;				// Attributs de l'arc
	BOOL select;				// selectionné ou non
}ARC;


/* Structure Sommet */
typedef struct sSommet{
	int num;				// nom du sommet
	char out;				// valeurs de sortie (tableau de 2 si implémentation de Mealy)	
	char adj[2];			// liste d'adjacence qui se calque sur le tableau de génération de graphe d'états vu en électronique
	BOOL select;			// selectionné ou non
}Sommet;
typedef Sommet *pSommet;

/* Structure Graphe */
typedef struct sGraphe{
	pSommet tabSommets;	// tableau de sommets
	int nbSommets;			// nombre de sommets
}Graphe;
typedef Graphe *pGraphe;

/* Fonctions */
/*---------------------creerGraphe()-----------------------
Creation d'un graphe aleatoire
Retourne le graphe obtenu, ou NULL en cas d'erreur

ARGS:	int n:					nombre de sommets
BOOL: oriente:	oriente ou non?

VARS: int i, j:				Variables de boucle
int temp:				Valeur aleatoire pour la matrice
pGraphe pG:			Graphe
pSommet pS:			tableau de Sommets
ATTRIBUT **mat:	Matrice de contiguite

---------------------------------------------------------*/
pGraphe creerGraphe();

/*------------------------freeGraphe()------------------------
Liberation d'une structure Graphe
Retourne 1 en cas de succes, autre valeur sinon

ARGS:	pGraphe pG:	Pointeur sur graphe a liberer

VARS: int i:			Variable de boucle
--------------------------------------------------------------*/
int freeGraphe(pGraphe pG);

#endif
