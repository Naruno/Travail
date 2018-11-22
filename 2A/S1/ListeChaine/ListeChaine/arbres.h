#pragma once
#ifndef ARBRES_H
#define ARBRES_H

typedef struct sTreeNode treeNode;

struct sTreeNode
{
	void* m_data;
	char type;
	char avl;
	treeNode * m_left; 
	treeNode * m_right;
};
//0 - char   1 - int
treeNode * creerNoeudArbre(void* p_value, char type, char avl);
void libererArbre(treeNode ** p_ppRoot);

void ajoutGauche(treeNode * p_pRoot, void* p_value, char type);
void ajoutDroite(treeNode * p_pRoot, void* p_value, char type);

int hauteur(treeNode * p_pRoot);
int taille(treeNode * p_pRoot);
int nbFeuilles(treeNode * p_pRoot);

void supprSousArbre(treeNode ** p_ppRoot, int p_value);

void afficher_noeud(treeNode * p_pRoot);
void afficher_Arbre(treeNode * p_pRoot, int profondeur);
void affichage_propre(char* message, treeNode * p_pRoot);

void parcoursPrefixe(treeNode * p_pRoot);
void parcoursInfixe(treeNode * p_pRoot);
void parcoursPostfixe(treeNode * p_pRoot);

void test_Arbre();
#endif
