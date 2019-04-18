#ifndef GRAPHES
#define GRAPHES

#include <stdio.h>
#include <stdlib.h>

typedef struct graphe_s Sommet;
typedef struct arc_s Arc;
typedef struct file_s file;

struct graphe_s {
	char m_etiquette;
	char m_visite;
	Arc* m_liste_arc;
};

struct arc_s {
	int m_attribut;
	Sommet* m_sommet;
	Arc* m_suivant;
};

struct file_s {
	Sommet* m_sommet;
	file *m_suivant;
};

Sommet* creerSommet(char p_etiquette);
Arc* creerArc(int p_attribut);


void libererListe(Arc* p_liste);
void libererGraphe(Sommet* graphe);
void profondeur(Sommet* graphe);

file* creerFile(Sommet* graphe);
void enfiler(file** p_file, Sommet* p_graphe);
Sommet* defiler(file **p_file);
void printListe(file* p_file);
void largeur(Sommet* graphe);

void ajouterSommet(Arc** p_liste, char p_etiquette);


#endif // !GRAPHES