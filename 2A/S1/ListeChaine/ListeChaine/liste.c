#pragma once
#include "liste.h"
#include <Windows.h>
#include <stdio.h>

Element* createListNode(int p_value) {
	// Cette fonction initialise une liste avec un premier element egal à 0.	
	Element* element = (Element*)calloc(1, sizeof(*element));

	if (!element) {
		printf("Erreur lors de l'allocation de list ou element.\n");
		exit(EXIT_FAILURE);
	}
	element->m_data = p_value;
	element->m_next = NULL;
	
	return element;
}

Element* addFirst(Element* p_pRoot, int p_value) {
	// Cette fonction ajoute un élément en début de liste.
	Element* nouveau = createListNode(p_value);
	if (!p_pRoot || !nouveau) {
		printf("Impossible d'inserer un element dans une liste vide ou Erreur d'allocation du nouvel element.\n");
		exit(EXIT_FAILURE);
	}	
	nouveau->m_next = p_pRoot;	
	return nouveau;
}

Element* pop(Element* p_pRoot, int* p_result) {
	// Cette fonction supprime un élément en début de liste.
	if (!p_pRoot) {
		printf("Impossible de supprimer une élément d'une liste vide.\n");
		exit(EXIT_FAILURE);
	}
	else{
		Element* aSupprimer = p_pRoot;
		*p_result = p_pRoot->m_data;
		p_pRoot = p_pRoot->m_next;
		free(aSupprimer);
		return p_pRoot;
	}
}

Element* addLast(Element* p_pRoot, int p_value) {
	// Cette fonction ajoute un élément en fin de liste de manière récursive.	
	
	if (!p_pRoot ) {		
		return createListNode(p_value);
	}
	p_pRoot->m_next = addLast(p_pRoot->m_next, p_value);
	return p_pRoot;
}

void freeList(Element * p_pRoot) {
	
	if (!p_pRoot) {
		printf("Impossible de libérer une liste vide.\n");
		exit(EXIT_FAILURE);
	}
	Element* actuel = p_pRoot;
	Element* suivant = p_pRoot;
	while (actuel->m_next != NULL) {
		suivant = suivant->m_next;
		actuel = NULL;
		free(actuel);
		actuel = suivant;
	}	
}

Element* popLast(Element* p_element) {
	// Cette fonction supprime un élément en fin de liste de maniere recursive.	

	if (!p_element) {
		printf("Impossible de supprimer un noeud d'une liste vide.\n");
		exit(EXIT_FAILURE);
	}	
	if (!p_element->m_next) {

		Element* aSupprimer = p_element;
		p_element = NULL;
		free(aSupprimer);
		return p_element;
	}
	else {
		p_element->m_next = popLast(p_element->m_next);
		return p_element;
	}
}

void printList(Element* p_pRoot) {
	// Cette fonction affiche une liste.
	if (!p_pRoot) {
		printf("Impossible d'afficher une liste vide.\n");
		exit(EXIT_FAILURE);
	}
	Element* actuel = p_pRoot;
	while (actuel) {
		printf("%d -> ", actuel->m_data);
		actuel = actuel->m_next;
	}
	printf("NULL\n");
}

Element* addSortAsc(Element* p_element, int p_value) {
	// Cette fonction insere un element en respectant l'ordre du membre m_data.	
	if (!p_element || p_value < p_element->m_data) {

		Element* nouveau = createListNode(p_value);
		nouveau->m_next = p_element;
		return nouveau;
	}
	else {
		p_element->m_next = addSortAsc(p_element->m_next, p_value);
		return p_element;
	}
}

void addSortAsco(Element** p_element, int p_value) {
	// Cette fonction insere un element en respectant l'ordre du membre m_data en utilisant un passage par adresse.
	
	if (!p_element || p_value < (*p_element)->m_data) {

		Element* nouveau = createListNode(p_value);
		nouveau->m_next = *p_element;
		*p_element = nouveau;
		return;
	}
	else {
		addSortAsco(&((*p_element)->m_next), p_value);
		return;
	}
}

Element* addSortDesc(Element* p_element, int p_value) {

	// Cette fonction insere un element en respectant l'ordre décroissant du membre m_data.	
	if (!p_element || p_value > p_element->m_data) {

		Element* nouveau = createListNode(p_value);
		nouveau->m_next = p_element;
		return nouveau;
	}
	else {
		p_element->m_next = addSortDesc(p_element->m_next, p_value);
		return p_element;
	}
}

int listLength(Element * p_pRoot) {	
	int taille = 0;
	Element* actuel = p_pRoot;
	while (actuel != NULL){

		actuel = actuel->m_next;
		taille++;
	}
	return taille;
}

Element* at(Element * p_pRoot, int p_index) {
	int i = 0;

	if (!p_pRoot) {
		printf("Impossible de trouver la valeur d'un indice dans une liste vide.\n");
		exit(EXIT_FAILURE);
	}
	Element *reponse = p_pRoot;
	if (p_index < listLength(p_pRoot)) {
		
		for (i = 0; i < p_index; i++) {
			reponse = reponse->m_next;
		}
		//reponse->m_next = NULL; // On demande uniquement le noeud, ou tout ce qu'il y a à partir du noeud ?
		return reponse;
	}
	else {
		printf("Cet indexe n'existe pas dans la liste.\nLa liste entiere sera renvoyee.\n");
		return p_pRoot;
	}	
}