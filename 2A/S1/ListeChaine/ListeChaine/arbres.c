#pragma once
#include "arbres.h"
#include <Windows.h>
#include <stdio.h>

treeNode * creerNoeudArbre(int p_value) {

	treeNode* noeud = (treeNode*)calloc(1, sizeof(*noeud));

	if (!noeud) {
		printf("Erreur lors de l'allocation de list ou node.\n");
		return NULL;
	}
	noeud->m_data = p_value;
	noeud->m_left = NULL;
	noeud->m_right = NULL;

	return noeud;
}

void libererArbre(treeNode ** p_ppRoot) {

	if (!(*p_ppRoot)) {
		return;
	}
	libererArbre(&(*p_ppRoot)->m_left);
	libererArbre(&(*p_ppRoot)->m_right);;
	free(*p_ppRoot);
	*p_ppRoot = NULL;
	return;
}

void ajoutGauche(treeNode * p_pRoot, int p_value) {

	if (!p_pRoot) {
		printf("Le noeud n'existe pas\n"); // OK ?
		return;
	}
	p_pRoot->m_left = creerNoeudArbre(p_value);

}

void ajoutDroite(treeNode * p_pRoot, int p_value) {

	if (!p_pRoot || p_pRoot->m_right ) {
		printf("Le noeud n'existe pas\n"); // OK ?
		return;
	}
	p_pRoot->m_right = creerNoeudArbre(p_value);
	
}

int hauteur(treeNode * p_pRoot) {

	if (!p_pRoot || (!p_pRoot->m_left) && (!p_pRoot->m_right)) {
		return 0;
	}
	int a = hauteur(p_pRoot->m_left);
	int b = hauteur(p_pRoot->m_right);
	
	return (a > b) ? a + 1: b + 1;
}

int taille(treeNode * p_pRoot) {

	if (!p_pRoot) {
		return 0;		
	}
	return taille(p_pRoot->m_left) + 1 + taille(p_pRoot->m_right);
}

int nbFeuilles(treeNode * p_pRoot) { 
	
	if (!p_pRoot) {
		return 0;
	}
	int a = 0, b = 0;
	if (!p_pRoot->m_left && !p_pRoot->m_right) {
		return 1;
	}
	a = nbFeuilles(p_pRoot->m_left);
	b = nbFeuilles(p_pRoot->m_right);
	return a + b;
}

void supprSousArbre(treeNode ** p_ppRoot, int p_value) {

	if (!(*p_ppRoot) || !(*p_ppRoot)->m_left && !(*p_ppRoot)->m_right) {
		return;
	}
	if ((*p_ppRoot)->m_data == p_value) {
		libererArbre(&(*p_ppRoot));
		return;
	}
	supprSousArbre(&(*p_ppRoot)->m_left, p_value);
	supprSousArbre(&(*p_ppRoot)->m_right, p_value);

}

void parcoursPrefixe(treeNode * p_pRoot) {

	if (p_pRoot) {	
		printf("[%d]", p_pRoot->m_data);
		if (p_pRoot->m_left) {
			parcoursPrefixe(p_pRoot->m_left);
		}
		if (p_pRoot->m_right) {
			parcoursPrefixe(p_pRoot->m_right);
		}
	}
}

void parcoursInfixe(treeNode * p_pRoot) {

	if ((!p_pRoot->m_left) && (!p_pRoot->m_right)) {
		printf("[%d]", p_pRoot->m_data);
		return;
	}
	if (p_pRoot->m_left) {
		parcoursInfixe(p_pRoot->m_left);
	}
	printf("[%d]", p_pRoot->m_data);
	if (p_pRoot->m_right) {
		parcoursInfixe(p_pRoot->m_right);
	}
}

void parcoursPostfixe(treeNode * p_pRoot) {

	if ((!p_pRoot->m_left) && (!p_pRoot->m_right)) {
		printf("[%d]", p_pRoot->m_data);
		return;
	}
	if (p_pRoot->m_left) {
		parcoursPostfixe(p_pRoot->m_left);
	}	
	if (p_pRoot->m_right) {
		parcoursPostfixe(p_pRoot->m_right);		
	}
	printf("[%d]", p_pRoot->m_data);	
}

void testTree() {

	treeNode * arbre = creerNoeudArbre(1);
	ajoutGauche(arbre, 2);
	ajoutDroite(arbre, 5);

	ajoutGauche(arbre->m_left, 3);
	ajoutGauche(arbre->m_right, 6);	

	ajoutDroite(arbre->m_left, 4);
	ajoutGauche(arbre->m_right->m_left, 7);
	ajoutDroite(arbre->m_right->m_left, 8);
	
	parcoursPostfixe(arbre);
	printf("\n");
	parcoursInfixe(arbre);
	printf("\n");
	printf("L'arbre est de hauteur : %d\n", hauteur(arbre));
	printf("L'arbre est de taille : %d\n", taille(arbre));
	printf("L'arbre a %d feuilles\n", nbFeuilles(arbre));

	return;
}