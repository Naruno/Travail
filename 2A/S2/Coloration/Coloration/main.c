#define _CRT_SECURE_NO_WARNINGS
#include "fonctions.h"

int main() {

	//FILE* fichier = fopen("gcol1.txt", "r");
	FILE* fichier = fopen("test.txt", "r");
	if (!fichier) {
		printf("Erreur fichier\n");
		return 0;
	}
	Graphe* graphe = lireFichier(fichier);

	int i, j, borne = graphe->N, **tab = graphe->tableau;
	
	for (i = 0; i < borne; i++) {
		printf("%d : ", i);
		for (j = 0; j < borne; j++) 
			printf("[%d]", tab[i][j]);			
		printf("\n");
	}
	printf("\n");
	Degsommet* deg = degretrie(graphe);
	for (i = 0; i < borne; i++) {
		printf("[%d|%d]-", deg[i].num, deg[i].deg);
	}
	printf("NULL\n");

	Colorer(deg, borne, graphe);

	for (i = 0; i < borne; i++) {
		printf("[%d]-", deg[i].color);
	}
	printf("NULL\n");
	system("pause");
	return 0;
}