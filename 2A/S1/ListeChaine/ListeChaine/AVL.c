#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "AVL.h"
#include "ABR.h"
#include "affichage.h"

void rotation(treeNode** p_Root, int sens) {

	if (sens != 0 && sens != 1) {
		print("Erreur de paramètre dans la fonction de rotation.\nUtilisation : \nsens = 0 -> rotation à gauche.\nsens = 1 -> rotation à droite.\n");
		return;
	}
	treeNode* var = NULL;	
	treeNode* var2 = *p_Root;
	if (sens == 0) {	
		var = (*p_Root)->m_right;	
		var2->m_right = NULL;
		var2->m_right = var->m_left;	
		var->m_left = NULL;	
		var->m_left = var2;	
	}
	else {		
		var = (*p_Root)->m_left;	
		var2->m_left = NULL;
		var2->m_left = var->m_right;		
		var->m_right = NULL;
		var->m_right = var2;	
	}
	*p_Root = var;	
	return;
}

int facteur_equilibre(treeNode* p_Root) {
	
	return hauteur(p_Root->m_right) - hauteur(p_Root->m_left);
}

void test_AVL() {
	treeNode* arbre = creerNoeudArbre(50, 1);
	ajout(arbre, 40, 1);
	ajout(arbre, 45, 1);
	ajout(arbre, 35, 1);
	ajout(arbre, 60, 1);
	ajout(arbre, 55, 1);
	ajout(arbre, 65, 1);
	ajout(arbre, 56, 1);
	ajout(arbre, 33, 1);
	ajout(arbre, 32, 1);
	affichage_propre("arbre de test\n", arbre);
	//rotation(&arbre, 0);
	printf("Facteur equilibre de l'arbre : %d\n", facteur_equilibre(arbre));
	rotation(&arbre, 1);
	affichage_propre("arbre de test après la rotation\n", arbre);
	
	return;
}