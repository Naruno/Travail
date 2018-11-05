#ifndef ABR_H
#define ABR_H

#include "arbres.h"
treeNode ** rechercher(treeNode ** p_pRoot, void* p_value);
void ajout(treeNode * p_pRoot, void* p_value, int type);
void suppression(treeNode ** p_pRoot, void* p_value);
void testRecherche();
#endif 