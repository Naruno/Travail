#pragma once
#include "liste.h"
#include <Windows.h>
#include <stdio.h>

Liste* initialisation() {
	// Cette fonction initialise une liste avec un premier element egal à 0.

	Liste* liste = (Liste*)calloc(1, sizeof(*liste));
	Element* element = (Element*)calloc(1, sizeof(*element));

	if (!liste || !element) {
		printf("Erreur lors de l'allocation de list ou element.\n");
		exit(EXIT_FAILURE);
	}
	element->m_nombre = 0;
	element->m_suivant = NULL;
	liste->m_premier = element;
	return liste;
}

void dInsertion(Liste* p_liste, int p_nombre) {
	// Cette fonction ajoute un élément en début de liste.
	Element* nouveau = (Element*)calloc(1, sizeof(*nouveau));
	if (!p_liste || !nouveau) {
		printf("Impossible d'inserer un element dans une liste vide ou Erreur d'allocation du nouvel element.\n");
		exit(EXIT_FAILURE);
	}	
	nouveau->m_nombre = p_nombre;
	nouveau->m_suivant = p_liste->m_premier;
	p_liste->m_premier = nouveau;
}

void dSuppression(Liste* p_liste) {
	// Cette fonction supprime un élément en début de liste.
	if (!p_liste) {
		printf("Impossible de supprimer une élément d'une liste vide.\n");
		exit(EXIT_FAILURE);
	}
	if (p_liste->m_premier != NULL) {
		Element* aSupprimer = p_liste->m_premier;
		p_liste->m_premier = p_liste->m_premier->m_suivant;
		free(aSupprimer);
	}
}

void insertionF(Liste* p_liste, int p_nombre) {
	// Cette fonction ajoute un élément en fin de liste.
	Element* nouveau = (Element*)calloc(1, sizeof(*nouveau));
	Element* actuel = (Element*)calloc(1, sizeof(*actuel));
	if (!p_liste || !nouveau || !actuel) {
		printf("Impossible d'inserer un element dans une liste vide ou Erreur d'allocation du nouvel element.\n");
		exit(EXIT_FAILURE);
	}
	nouveau->m_nombre = p_nombre;
	nouveau->m_suivant = NULL;
	actuel = p_liste->m_premier;
	while (actuel->m_suivant != NULL) {
		actuel = actuel->m_suivant;
	}
	actuel->m_suivant = nouveau;	
}

Element* insertionFRec(Element* p_element, Element* p_nouveau) {
	// Cette fonction ajoute un élément en fin de liste de manière récursive.
	if (!p_nouveau) {
		return p_element;
	}
	if (!p_element) {

		p_nouveau->m_suivant = p_element;
		return p_nouveau;
	}
	else {
		p_element->m_suivant = insertionFRec(p_element->m_suivant, p_nouveau);
		return p_element;
	}
}

void suppressionF(Liste* p_liste) {
	// Cette fonction supprime un élément en fin de liste.	
	Element* actuel = (Element*)calloc(1, sizeof(*actuel));
	if (!p_liste || !actuel || !p_liste->m_premier ) {
		printf("Impossible de supprimer une élément d'une liste vide.\n");
		exit(EXIT_FAILURE);
	}

	actuel = p_liste->m_premier;
	while (actuel->m_suivant->m_suivant != NULL) {
		
		actuel = actuel->m_suivant;
	}
	
	Element* aSupprimer = actuel->m_suivant;
	actuel->m_suivant = NULL;	
	free(aSupprimer);
}

Element* suppressionFRec(Element* p_element) {
	// Cette fonction supprime un élément en fin de liste de maniere recursive.	
	
	if (!p_element->m_suivant) {		

		Element* aSupprimer = p_element;
		p_element = NULL;		
		free(aSupprimer);
		return NULL;
	}
	else {
		p_element->m_suivant = suppressionFRec(p_element->m_suivant);
		return p_element;
	}
}

void afficherListe(Liste* p_liste) {
	// Cette fonction affiche une liste.
	if (!p_liste) {
		printf("Impossible d'afficher une liste vide.\n");
		exit(EXIT_FAILURE);
	}
	Element* actuel = p_liste->m_premier;
	while (actuel) {
		printf("%d -> ", actuel->m_nombre);
		actuel = actuel->m_suivant;
	}
	printf("NULL\n");
}

Element* ajoutTriCroissant(Element* p_element, Element* p_nouveau) {
	// Cette fonction insere un element en respectant l'ordre du membre m_nombre.
	if (!p_nouveau) {
		return p_element;
	}
	if (!p_element || p_nouveau->m_nombre < p_element->m_nombre) {

		p_nouveau->m_suivant = p_element;
		return p_nouveau;
	}
	else {
		p_element->m_suivant = ajoutTriCroissant(p_element->m_suivant, p_nouveau);
		return p_element;
	}
}

void ajoutTriCroissanto(Element** p_element, Element* p_nouveau) {
	// Cette fonction insere un element en respectant l'ordre du membre m_nombre en utilisant un passage par adresse.
	if (!p_nouveau) {
		return;
	}
	if(!p_element || p_nouveau->m_nombre < (*p_element)->m_nombre){

		p_nouveau->m_suivant = *p_element;
		*p_element = p_nouveau;
		return;
	}
	else {
		ajoutTriCroissanto(&((*p_element)->m_suivant) , p_nouveau);
		return;
	}	
}