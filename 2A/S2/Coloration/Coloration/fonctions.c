#define _CRT_SECURE_NO_WARNINGS
#include "fonctions.h"

Graphe* creerGraphe(int p_N) {
	int i, j;
	Graphe* graphe = (Graphe*)calloc(1, sizeof(*graphe));
	int** matrice = (int**)calloc(p_N, sizeof(*matrice));

	if (!matrice || !graphe) {
		printf("ENORME PROBLEME !!\n");
		return NULL;
	}
	for (i = 0; i < p_N; i++) {
		matrice[i] = (int*)calloc(p_N, sizeof(int));
		for (j = 0; j < p_N; j++) {
			matrice[i][j] = (i == j) ? 0 : -1; 
		}
	}
	graphe->N = p_N;
	graphe->tableau = matrice;	
	return graphe;
}

Graphe* lireFichier(FILE* p_file) {
	int i, N, from, to;
	fscanf(p_file, "p edge %d 2487\n", &N);
	Graphe* graphe = creerGraphe(N);

	while(fscanf(p_file, "e %d %d\n", &from, &to) != EOF){
		
		graphe->tableau[from-1][to-1] = 2;
		graphe->tableau[to-1][from-1] = 2;
	}
	fclose(p_file);
	return graphe;
}

Degsommet* degretrie(Graphe* p_graphe) {
	int **matrice = p_graphe->tableau, borne = p_graphe->N;
	char i, j, tab_en_ordre = 0;
	Degsommet* degre = (Degsommet*)calloc(borne, sizeof(*degre)), tmp;
	
	for (i = 0; i < borne; i++) {
		degre[i].num = i;
		degre[i].color = -1;
		for (j = i; j < borne; j++) {
			if (matrice[i][j] == 2) {
				degre[i].deg++;
				degre[j].deg++;
			}
		}
	}	
	while (!tab_en_ordre){

		tab_en_ordre = 1;
		for (i = 0; i < borne - 1; i++){
			if (degre[i].deg < degre[i + 1].deg){
				tmp = degre[i];
				degre[i] = degre[i + 1];
				degre[i + 1] = tmp;
				tab_en_ordre = 0;
			}
		}
		borne--;
	}
	return degre;
}

char ToutColor(Degsommet* p_tab, int p_taille) {
	
	char i;
	for (i = 0; i < p_taille; i++) {
		if (p_tab[i].color == -1) return 0;
	}
	return 1;
}

void Colorer(Degsommet* p_tab, int p_taille, Graphe* p_graphe) {

	int C = 0, i, j, indiceCouleur, couleur;
	while (!ToutColor(p_tab, p_taille)){
		
		for (i = 0; i < p_taille; i++) {
			if (p_tab[i].color == -1) {
				
				for (j = 0; j < p_taille; j++) {
					if (p_graphe->tableau[i][j] == 2) {
					
						indiceCouleur = degAssocie(p_tab, p_taille, j);
						couleur = p_tab[indiceCouleur].color;
						if (couleur == C) break;
						// A Verifier						
					}
					p_tab[i].color = C;
				}
			}			
		}
		C++;
	}
}

int degAssocie(Degsommet *p_tab, int taille, int indice) {
	int i;
	for (i = 0; i < taille; i++) {
		if (p_tab[i].num == indice) {
			return i;
		}
	}
	printf("Probleme !!!\n");
	return -1;
}