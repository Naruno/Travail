#pragma once
#ifndef AVL_H
#define AVL_H
#include "arbres.h"

//0 - gauche   1 - droite
void rotation(treeNode** p_Root, int sens);
int facteur_equilibre(treeNode* p_Root);
void equilibrer_noeud(treeNode** p_Root);
void test_AVL();
#endif