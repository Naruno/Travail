#include "ABR.h"
#include "AVL.h"

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
	return NULL;
}

void ajout(treeNode ** p_pRoot, void* p_value, char type) {
	if (!(*p_pRoot)) {
		return;
	}
	if (!(*p_pRoot)->m_left && !(*p_pRoot)->m_right) {
		if (p_value >= (*p_pRoot)->m_data) {
			(*p_pRoot)->m_right = creerNoeudArbre(p_value, type, (*p_pRoot)->avl);
			return;
		}
		if (p_value < (*p_pRoot)->m_data) {
			(*p_pRoot)->m_left = creerNoeudArbre(p_value, type, (*p_pRoot)->avl);
			return;
		}
	}
	if (p_value >= (*p_pRoot)->m_data) {

		if ((*p_pRoot)->m_right) {
			ajout(&((*p_pRoot)->m_right), p_value, type);
		}
		else {
			(*p_pRoot)->m_right = creerNoeudArbre(p_value, type, (*p_pRoot)->avl);
			return;
		}
		equilibrer_noeud(p_pRoot);
		//affichage_propre("noeud après équilibrage\n", *p_pRoot);
	}
	if (p_value < (*p_pRoot)->m_data) {
		if ((*p_pRoot)->m_left) {
			ajout(&((*p_pRoot)->m_left), p_value, type);
		}
		else {
			(*p_pRoot)->m_left = creerNoeudArbre(p_value, type, (*p_pRoot)->avl);
			return;
		}
		equilibrer_noeud(p_pRoot);
		//affichage_propre("noeud après équilibrage\n", *p_pRoot);
	}	
}

void suppression(treeNode ** p_pRoot, void* p_value) { 
	if ((*p_pRoot)->type == 1) {
		printf("Je supprime %d\n", (int)p_value);
	}
	if ((*p_pRoot)->type == 0) {
		printf("Je supprime %c\n", (char)p_value);
	}
	
	treeNode ** noeud = rechercher(p_pRoot, p_value);
	if (!noeud) {	
		if ((*p_pRoot)->type == 1) {
			printf("%d n existe pas dans cet arbre\n", (int)p_value);
			return;
		}
		if ((*p_pRoot)->type == 0) {
			printf("%c n existe pas dans cet arbre\n", (char)p_value);
			return;
		}
	}
	if (!(*noeud)) {		
		return;
	}
	if (!((*noeud)->m_left) && !((*noeud)->m_right)) {
		// On supprime la feuille.
		libererArbre(noeud);
		equilibrer_noeud(p_pRoot);
		return;
	}
	if (!((*noeud)->m_left) && (*noeud)->m_right) {	
		// On transforme le noeud en son fils.		
		*noeud = (*noeud)->m_right;		
		equilibrer_noeud(p_pRoot);
		return ;
	}
	if(((*noeud)->m_left) && !(*noeud)->m_right) {
		// On transforme le noeud en son fils.
		*noeud = (*noeud)->m_left;
		equilibrer_noeud(p_pRoot);
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
	equilibrer_noeud(p_pRoot);
	return;
}

treeNode* lineariser(treeNode* p_Root, treeNode* p_List) {

	if (!p_Root) {
		return p_List;
	}
	p_List = lineariser(p_Root->m_right, p_List);
	
	p_Root->m_right = p_List;	
	p_List = p_Root;
	p_List = lineariser(p_Root->m_left, p_List);	
	
	p_Root->m_left = NULL;
	return p_List;
}

treeNode* arboriser(treeNode* p_Root) {

	if (!p_Root) {
		return p_Root;
	}	
	int nb_neouds = hauteur(p_Root) + 1, i;

	if (nb_neouds == 1) {		
		return p_Root;
	}

	int noeud = (!nb_neouds % 2) ? nb_neouds / 2 : (nb_neouds + 1) / 2;
	treeNode* p_racine = p_Root;
	treeNode* p_left;
	treeNode* p_left_tmp;
	if (nb_neouds == 2) {
		p_left = NULL;
		p_left_tmp = NULL;
	}
	else {
		p_left = creerNoeudArbre(p_Root->m_data, p_Root->type, p_Root->avl);
		p_left_tmp = p_Root->m_right;
	}
	treeNode* p_right = p_Root;

	for (i = 1; i < noeud; i++) {
		p_racine = p_racine->m_right;
	}
	p_right = p_racine->m_right;
	
	if (p_left_tmp && p_left_tmp->m_right){
		while (p_left_tmp->m_data != p_racine->m_data) {
			ajout(&p_left, p_left_tmp->m_data, p_left_tmp->type);
			p_left_tmp = p_left_tmp->m_right;
		}
	}	
	p_racine->m_right = NULL;
	p_racine->m_right = arboriser(p_right);
	p_racine->m_left = arboriser(p_left);

	return p_racine;		
}

void test_ABR() {

	treeNode * arbre = creerNoeudArbre((char*)20, 1, 0);	
	ajout(&arbre, (char*)5, 1);
	ajout(&arbre, (char*)10, 1);
	ajout(&arbre, (char*)15, 1);
	ajout(&arbre, (char*)25, 1);	
	ajout(&arbre, (char*)30, 1);	
	ajout(&arbre, (char*)35, 1);	
	ajout(&arbre, (char*)40, 1);		
	affichage_propre("arbre\n", arbre);	
	suppression(&arbre, (char*)6);
	affichage_propre("arbre après suppression\n", arbre);
	treeNode * liste = NULL;
	treeNode * arbre_lineaire = lineariser(arbre, liste);
	affichage_propre("arbre linéaire\n", arbre_lineaire);
	treeNode * arbre_equilibre = arboriser(arbre_lineaire);
	
	affichage_propre("arbre équilibré\n", arbre_equilibre);
	libererArbre(&arbre);	
	return;
}