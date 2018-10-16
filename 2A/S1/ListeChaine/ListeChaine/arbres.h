#pragma once
#ifndef ARBRES_H
#define ARBRES_H

typedef struct sTreeNode treeNode;

struct sTreeNode
{
	int m_data;
	treeNode * m_left; 
	treeNode * m_right;
};

treeNode * creerNoeudArbre(int p_value);
void libererArbre(treeNode ** p_ppRoot);

void ajoutGauche(treeNode * p_pRoot, int p_value);
void ajoutDroite(treeNode * p_pRoot, int p_value);

int hauteur(treeNode * p_pRoot);
int taille(treeNode * p_pRoot);
int nbFeuilles(treeNode * p_pRoot);

void supprSousArbre(treeNode ** p_ppRoot, int p_value);

void parcoursPrefixe(treeNode * p_pRoot);
void parcoursInfixe(treeNode * p_pRoot);
void parcoursPostfixe(treeNode * p_pRoot);

void testTree();
#endif
