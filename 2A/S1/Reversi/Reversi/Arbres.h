#ifndef ARBRES_H
#define ARBRE_H
#include "Reversi.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct noeud noeud;
struct noeud {
	char m_valeur[8][8];  // Plateau de jeu.
	char m_score;		 // Score qui sera associé en conséquence du choix de cette configuration.
	char m_coords[2];	// Coordonnées pour arriver à cette configuration.
	char m_nb_enfants; // Nombre d'enfants.
	noeud* m_suivant; // Liste des frères suivants.
	noeud* m_enfant; // Liste d'enfants.
};

// Créer un noeud rempli par le tableau p_valeur avec les coordonnées (a,b)
noeud* creerListe(char p_valeur[8][8], char a, char b);
// Libere une liste.
void libererListe(noeud * p_liste);
// Ajoute un noeud en tête d'une liste. 
noeud* ajoutTete(noeud* p_pRoot, char  p_valeur[8][8], char a, char b);
// Fonction de debug pour afficher une liste.
void afficherListe(noeud* p_liste);
// Complete l'arbre des possibilités de jeu jusqu'a la profondeur voulue, joueur est à 0 et permet de determiner les coups pour chaque joueur selon la parité.
void construction(noeud **tete, char profondeur, char joueur);
// Renvoie le score associé à un noeud selon l'algorithme min-max avec élagage.
char MinMax(noeud **arbre, char joueur, char a, char b);
// Choisi le plus petit ou plus grans score parmis une liste selon la parité du joueur.
char choixScore(noeud *p_liste, char p_joueur);
// Recherche une cible parmis une liste et stocke les coordonnées associées dans p_joueur.
void recherche(noeud *p_liste, char(*p_joueur)[2], char cible);
// Fonction de debug pour afficher des coordonnées.
void afficherCoords(noeud* p_liste);
#endif // !ARBRES_H