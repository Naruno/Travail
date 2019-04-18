#include "graphes.h"

Sommet* creerSommet(char p_etiquette) {

	Sommet* graphe = (Sommet*)calloc(1, sizeof(*graphe));
	graphe->m_etiquette = p_etiquette;
	graphe->m_visite = 0;
	graphe->m_liste_arc = NULL;
	return graphe;
}

Arc* creerArc(int p_attribut) {

	Arc* arc = (Arc*)calloc(1, sizeof(*arc));
	arc->m_attribut = p_attribut;
	arc->m_sommet = NULL;
	arc->m_suivant = NULL;
	return arc;
}

void libererListe(Arc* p_liste) {	

	if (!p_liste) return;
	
	libererListe(p_liste->m_suivant);
	libererListe(p_liste->m_sommet->m_liste_arc);
	
	free(p_liste->m_sommet);
	p_liste->m_sommet = NULL;
	free(p_liste);	
	p_liste = NULL;
}

void libererGraphe(Sommet* graphe) {
	libererListe(graphe->m_liste_arc);
	free(graphe);
}

void ajouterSommet(Arc** p_liste, char p_etiquette) {

	if (!(*p_liste)) {
		*p_liste = creerArc(0);
		(*p_liste)->m_sommet = creerSommet(p_etiquette);
		return;
	}	
	ajouterSommet(&(*p_liste)->m_suivant, p_etiquette);	
}

void profondeur(Sommet* graphe) {

	if (graphe->m_visite == 0) {
		printf("[%c]", graphe->m_etiquette);
		graphe->m_visite = 1;
		Arc* tempo = graphe->m_liste_arc;
		while (tempo != NULL) {

			profondeur(tempo->m_sommet);
			tempo = tempo->m_suivant;
		}
	}
}

file* creerFile(Sommet* graphe) {

	file* n_file = (file*)malloc( sizeof(*n_file));

	n_file->m_sommet = graphe;
	n_file->m_suivant = NULL;
	return n_file;
}

void enfiler(file **p_file, Sommet* p_graphe){

	file *nouveau = malloc(sizeof(*nouveau));

	if (nouveau == NULL)	{
		printf("Oups1\n");
		return;
	}
	nouveau->m_sommet = p_graphe;
	nouveau->m_suivant = NULL;
	
	if (*p_file) {
		file *elementActuel = *p_file;
		/* On se positionne à la fin de la file */
		while (elementActuel->m_suivant){
			elementActuel = elementActuel->m_suivant;
		}
		elementActuel->m_suivant = nouveau;
		return;
	}
	*p_file = nouveau;
}

Sommet* defiler(file **p_file){

	if (!*p_file){
		printf("Oups 2\n");
		return NULL;
	}
	char nombreDefile = 0;
	/* On vérifie s'il y a quelque chose à défiler */
	file *elementDefile = NULL;
	if (*p_file){

		elementDefile = *p_file;
		nombreDefile = (*p_file)->m_sommet->m_etiquette;
		*p_file = (*p_file)->m_suivant;
		//free(elementDefile);
	}
	printf("[%c]\n", nombreDefile);
	return elementDefile->m_sommet;
}

void printListe(file* p_file){
	 
	if (!p_file) {
		printf("NULL\n");
		return;
	}	
	printf("[%c]->", p_file->m_sommet->m_etiquette);
	printListe(p_file->m_suivant);
}

void largeur(Sommet* graphe) {
	
	file* liste = NULL;
	enfiler(&liste, graphe);
	while (liste) {
		graphe = defiler(&liste);

		Arc* tempo = graphe->m_liste_arc;
		while (tempo) {
			if (tempo->m_sommet->m_visite == 0) {
				tempo->m_sommet->m_visite = 1;
				enfiler(&liste, tempo->m_sommet);				
			}
			tempo = tempo->m_suivant;
		}
	}	
}
