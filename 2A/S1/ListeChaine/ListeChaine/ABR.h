#ifndef ABR_H
#define ABR_H
#include "arbres.h"
treeNode ** rechercher(treeNode ** p_pRoot, void* p_value);
//0 - char   1 - int
void ajout(treeNode * p_pRoot, void* p_value, int type);
void suppression(treeNode ** p_pRoot, void* p_value);
treeNode* lineariser(treeNode* p_Root, treeNode* p_List);
treeNode* arboriser(treeNode* p_Root);
void test_ABR();
#endif 