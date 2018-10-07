#pragma once
#include "liste.h"
#include <Windows.h>
#include <stdio.h>

node* createListNode(void* p_value) {
	// Cette fonction initialise une liste avec un premier node egal à 0.	
	node* noeud = (node*)calloc(1, sizeof(*noeud));

	if (!noeud) {
		printf("Erreur lors de l'allocation de list ou node.\n");
		exit(EXIT_FAILURE);
	}
	noeud->m_data = p_value;
	noeud->m_next = NULL;
	
	return noeud;
}

node* addFirst(node* p_pRoot, void* p_value) {
	// Cette fonction ajoute un élément en début de liste.
	node* nouveau = createListNode(p_value);
	if (!p_pRoot || !nouveau) {
		printf("Impossible d'inserer un node dans une liste vide ou Erreur d'allocation du nouvel node.\n");
		exit(EXIT_FAILURE);
	}	
	nouveau->m_next = p_pRoot;	
	return nouveau;
}

node* pop(node* p_pRoot, void** p_result) {
	// Cette fonction supprime un élément en début de liste.
	if (!p_pRoot) {
		printf("Impossible de supprimer une élément d'une liste vide.\n");
		exit(EXIT_FAILURE);
	}
	else{
		node* aSupprimer = p_pRoot;
		*p_result = p_pRoot->m_data;
		p_pRoot = p_pRoot->m_next;
		free(aSupprimer);
		return p_pRoot;
	}
}

node* addLast(node* p_pRoot, void* p_value) {
	// Cette fonction ajoute un élément en fin de liste de manière récursive.	
	
	if (!p_pRoot ) {		
		return createListNode(p_value);
	}
	p_pRoot->m_next = addLast(p_pRoot->m_next, p_value);
	return p_pRoot;
}

void freeList(node * p_pRoot) {
	
	if (!p_pRoot) {
		return;
	}
	freeList(p_pRoot->m_next);
	free(p_pRoot);
}

node* popLast(node* p_node) {
	// Cette fonction supprime un élément en fin de liste de maniere recursive.	

	if (!p_node) {
		printf("Impossible de supprimer un noeud d'une liste vide.\n");
		exit(EXIT_FAILURE);
	}	
	if (!p_node->m_next) {

		node* aSupprimer = p_node;
		p_node = NULL;
		free(aSupprimer);
		return p_node;
	}
	else {
		p_node->m_next = popLast(p_node->m_next);
		return p_node;
	}
}

void printList_int(node* p_pRoot) {
	// Cette fonction affiche une liste.
	if (!p_pRoot) {
		printf("NULL\n");
		return;
	}
	printf("%d -> ", (int*)p_pRoot->m_data);
	printList_int(p_pRoot->m_next);
}
void printList_str(node* p_pRoot) {
	// Cette fonction affiche une liste.
	if (!p_pRoot) {
		printf("NULL\n");
		return;
	}
	printf("%s -> ", (char**)p_pRoot->m_data);
	printList_str(p_pRoot->m_next);
}

node* addSortAsc(node* p_node, void* p_value) {
	// Cette fonction insere un node en respectant l'ordre du membre m_data.	
	if (!p_node || p_value < p_node->m_data) {

		node* nouveau = createListNode(p_value);
		nouveau->m_next = p_node;
		return nouveau;
	}
	else {
		p_node->m_next = addSortAsc(p_node->m_next, p_value);
		return p_node;
	}
}

void addSortAsco(node** p_node, void* p_value) {
	// Cette fonction insere un node en respectant l'ordre du membre m_data en utilisant un passage par adresse.
	
	if (!p_node || p_value < (*p_node)->m_data) {

		node* nouveau = createListNode(p_value);
		nouveau->m_next = *p_node;
		*p_node = nouveau;
		return;
	}
	else {
		addSortAsco(&((*p_node)->m_next), p_value);
		return;
	}
}

node* addSortDesc(node* p_node, void* p_value) {

	// Cette fonction insere un node en respectant l'ordre décroissant du membre m_data.	
	if (!p_node || p_value > p_node->m_data) {

		node* nouveau = createListNode(p_value);
		nouveau->m_next = p_node;
		return nouveau;
	}
	else {
		p_node->m_next = addSortDesc(p_node->m_next, p_value);
		return p_node;
	}
}

int listLength(node * p_pRoot) {	
	int taille = 0;
	node* actuel = p_pRoot;
	while (actuel != NULL){

		actuel = actuel->m_next;
		taille++;
	}
	return taille;
}

node* at(node * p_pRoot, int p_index) {
	int i = 0;

	if (!p_pRoot) {
		printf("Impossible de trouver la valeur d'un indice dans une liste vide.\n");
		exit(EXIT_FAILURE);
	}
	node *reponse = p_pRoot;
	if (p_index < listLength(p_pRoot)) {
		
		for (i = 0; i < p_index; i++) {
			reponse = reponse->m_next;
		}
		
		return reponse;
	}
	else {
		printf("Cet indexe n'existe pas dans la liste.\nLa liste entiere sera renvoyee.\n");
		return p_pRoot;
	}	
}

void Hanoi(int n, node* D, node* A, node* I) {
	int value;
	if (n != 0) {
		Hanoi(n - 1, D, I, A);
		D = pop(D, &value);
		A = addFirst(A, value);

		Hanoi(n - 1, I, A, D);
	}	
}

void Test_List() {

	node* maListe = createListNode(2);
	node* res;
	int a = 0;
	printList_int(maListe);

	maListe = addLast(maListe, 10);
	printList_int(maListe);
	addSortAsco(&maListe, 7);
	maListe = addLast(maListe, 99);
	printList_int(maListe);
	a = listLength(maListe);
	res = at(maListe, a - 1);

	printf("taille liste = %d\n", a);
	printList_int(res);
	printList_int(maListe);
	maListe = pop(maListe, &a);
	printList_int(maListe);
	system("pause");

	freeList(maListe);
}