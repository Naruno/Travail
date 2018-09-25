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
	
	Element* actuel = p_pRoot;
	Element* suivant = p_pRoot;
	while (actuel->m_next != NULL) {
		suivant = suivant->m_next;
		actuel = NULL;
		free(actuel);
		actuel = suivant;
	}	
}

Element* insertionFRec(Element* p_element, Element* p_nouveau) {
	// Cette fonction ajoute un élément en fin de liste de manière récursive.
	if (!p_nouveau) {
		return p_element;
	}
	if (!p_element) {

		p_nouveau->m_next = p_element;
		return p_nouveau;
	}
	else {
		p_element->m_next = insertionFRec(p_element->m_next, p_nouveau);
		return p_element;
	}
}

Element* suppressionF(Element* p_pRoot) {
	// Cette fonction supprime un élément en fin de liste.	

	//Element* actuel = (Element*)calloc(1, sizeof(*actuel));
	Element* actuel = p_pRoot;
	if (!actuel) {
		printf("Impossible de supprimer une élément d'une liste vide.\n");
		exit(EXIT_FAILURE);
	}

	//actuel = p_pRoot;
	while (actuel->m_next->m_next != NULL) {

		actuel = actuel->m_next;
	}

	Element* aSupprimer = actuel->m_next;
	actuel->m_next = NULL;
	free(aSupprimer);
	return actuel;
}

Element* suppressionFRec(Element* p_element) {
	// Cette fonction supprime un élément en fin de liste de maniere recursive.	

	if (!p_element->m_next) {

		Element* aSupprimer = p_element;
		p_element = NULL;
		free(aSupprimer);
		return NULL;
	}
	else {
		p_element->m_next = suppressionFRec(p_element->m_next);
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