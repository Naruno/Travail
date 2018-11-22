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
		var2->m_right = var->m_left;
		var->m_left = var2;	
	}
	else {		
		var = (*p_Root)->m_left;			
		var2->m_left = var->m_right;	
		var->m_right = var2;	
	}
	*p_Root = var;	
	return;
}

int facteur_equilibre(treeNode* p_Root) {
	if (!p_Root) {
		return 0;
	}
	if (!p_Root->m_left) {
		return hauteur(p_Root->m_right);
	}
	if (!p_Root->m_right) {
		return -hauteur(p_Root->m_left);
	}
	return hauteur(p_Root->m_right) - hauteur(p_Root->m_left);
}

void equilibrer_noeud(treeNode** p_Root) {
	int equilibre = facteur_equilibre(*p_Root);
	if (((*p_Root)->avl == 1) && (equilibre > 1 || equilibre < -1)) {

		int equilibre_gauche = facteur_equilibre((*p_Root)->m_left);
		int equilibre_droite = facteur_equilibre((*p_Root)->m_right);
	
		if (equilibre == 2) {
			if (equilibre_droite == 1) {
				rotation(p_Root, 0);	
				return;
			}
			if (equilibre_droite == -1) {
				rotation(p_Root, 1);
				rotation(p_Root, 0);		
				return;
			}
		}
		if (equilibre == -2) {
			if (equilibre_gauche == 1) {
				rotation(p_Root, 0);
				rotation(p_Root, 1);			
				return;
			}
			if (equilibre_gauche == -1) {
				rotation(p_Root, 1);			
				return;
			}
		}
	}
}

void test_AVL() {
	treeNode* arbre = creerNoeudArbre(1, 1, 1);
	
	ajout(&arbre, 2, 1);
	ajout(&arbre, 3, 1);
	ajout(&arbre, 4, 1);
	ajout(&arbre, 5, 1);
	ajout(&arbre, 6, 1);
	ajout(&arbre, 7, 1);
	ajout(&arbre, 8, 1);	
	ajout(&arbre, 9, 1);
	ajout(&arbre, 10, 1);	
	affichage_propre("arbre équilibré après l'ajout successif de 10 valeurs croissantes.\n", arbre);
	suppression(&arbre, 1);
	suppression(&arbre, 2);
	suppression(&arbre, 3);
	suppression(&arbre, 4);
	suppression(&arbre, 5);
	
	affichage_propre("arbre équilibré après la suppression successive de 5 valeurs croissantes.\n", arbre);	
	return;
}