#include "ABR.h"
#include <stdio.h>

treeNode ** rechercher(treeNode ** p_pRoot, void* p_value) {

	if (!(*p_pRoot)) {
		return NULL;
	}
	if (p_value == (*p_pRoot)->m_data) {
		return p_pRoot;
	}	
	if (p_value > (*p_pRoot)->m_data) {		
		return rechercher(&((*p_pRoot)->m_right), p_value);
	}
	if (p_value < (*p_pRoot)->m_data) {
		return rechercher(&((*p_pRoot)->m_left), p_value);
	}		
}

void ajout(treeNode * p_pRoot, void* p_value, int type) {
	if (!p_pRoot) {
		return creerNoeudArbre(p_value, type);
	}
	if (!p_pRoot->m_left && !p_pRoot->m_right) {
		if (p_value >= p_pRoot->m_data) {
			p_pRoot->m_right = creerNoeudArbre(p_value, type);
			return;
		}
		if (p_value < p_pRoot->m_data) {
			p_pRoot->m_left = creerNoeudArbre(p_value, type);
			return;
		}
	}
	if (p_value >= p_pRoot->m_data) {

		if (p_pRoot->m_right) {
			ajout(p_pRoot->m_right, p_value, type);			
		}
		else {
			p_pRoot->m_right = creerNoeudArbre(p_value, type);
			return;
		}
	}
	if (p_value < p_pRoot->m_data) {
		if (p_pRoot->m_left) {
			ajout(p_pRoot->m_left, p_value, type);
		}
		else {
			p_pRoot->m_left = creerNoeudArbre(p_value, type);
			return;
		}
	}	
}

void suppression(treeNode ** p_pRoot, void* p_value) { 
	printf("Je supprime %d\n", p_value);
	treeNode ** noeud = rechercher(p_pRoot, p_value);
	if (!noeud) {
		// A changer le jour ou on veut afficher autre chose qu'un (int).	
		printf("%d n existe pas dans cet arbre\n", p_value);
	}
	if (!(*noeud)) {		
		return;
	}
	if (!((*noeud)->m_left) && !((*noeud)->m_right)) {
		// On supprime la feuille.
		libererArbre(noeud);
		return;
	}
	if (!((*noeud)->m_left) && (*noeud)->m_right) {	
		// On transforme le noeud en son fils.		
		*noeud = (*noeud)->m_right;		
		return ;
	}
	if(((*noeud)->m_left) && !(*noeud)->m_right) {
		// On transforme le noeud en son fils.
		*noeud = (*noeud)->m_left;
		return ;
	}
	treeNode ** predecesseur = &((*noeud)->m_left);
	treeNode * tempo = (*noeud)->m_left;
	// On recherche le plus grand noeud des plus petits.
	while (tempo->m_right) {
		tempo = tempo->m_right;		
	}
	(*noeud)->m_data = tempo->m_data;		
	suppression(&(*predecesseur), tempo->m_data);
	return;
}

void testRecherche() {

	treeNode * arbre = creerNoeudArbre(50, 1);
	
	ajout(arbre, 40, 1);
	ajout(arbre, 70, 1);
	ajout(arbre, 35, 1);
	ajout(arbre, 75, 1);
	
	affichage_propre(arbre);
	
	suppression(&arbre, 75);
	affichage_propre(arbre);
	
	libererArbre(&arbre);
	return;
}