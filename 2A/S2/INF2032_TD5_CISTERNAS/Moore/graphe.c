#define _CRT_SECURE_NO_WARNINGS
#include "graphe.h"
#include <conio.h>

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

pGraphe creerGraphe(){	
	// Declaration des variables.
	int n, i, etat_suivant, sortie;
	pGraphe pG = NULL;
	pSommet pS = NULL;	
	// saisie du nombre de sommets dans le graphe.
	printf("Nombre de sommets dans le graphe ? > ");
	scanf("%d", &n);

	// Allocation memoire des sommets.
	pS = (pSommet)calloc(n, sizeof(*pS));	

	// Initialisation memoire du graphe.
	pG = (pGraphe)calloc(1, sizeof(*pG));

	// Saisie de la matrice de changement d'état.
	for (i = 0; i < n; i++) {
	
		pS[i].num = i;
		// Saisie de l'état si la commande est égale à 0.
		printf("\nEtat %d :\nVa dans quel etat si E = 0 ? > ", i);
		scanf("%d", &etat_suivant);		
		pS[i].adj[0] = etat_suivant;

		// Saisie de l'état si la commande est égale à 1.
		printf("Va dans quel etat si E = 1 ? > ");
		scanf("%d", &etat_suivant);		
		pS[i].adj[1] = etat_suivant;

		// Saisie de la sortie correspondant à l'état.
		printf("Sortie = ");
		scanf("%d", &sortie);
		// Remplissage de l'état.	
		pS[i].out = sortie;
	}
	// Remplissage de la structure finale
	pG->nbSommets = n;
	pG->tabSommets = pS;
	return pG;
}

/*------------------------freeGraphe()------------------------
Liberation d'une structure Graphe
Retourne 1 en cas de succes, autre valeur sinon

ARGS:	pGraphe pG:	Pointeur sur graphe a liberer

VARS: int i:			Variable de boucle
--------------------------------------------------------------*/
int freeGraphe(pGraphe pG){

	// Analyse des arguments
	if (pG->tabSommets) free(pG->tabSommets);	
	// Liberation du graphe
	free(pG);	
	return 1;
}
