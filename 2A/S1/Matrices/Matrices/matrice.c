#define _CRT_SECURE_NO_WARNINGS
#include "matrice.h"

Matrice *ChargerMatrice(char *path) {
	Matrice *m;
	int i, j, hauteur, largeur;

	FILE *fichier = fopen(path, "r");
	if (fichier != NULL) { // On vérifie que le fichier ouvert est valide

		fscanf(fichier, "%d*%d\n", &hauteur, &largeur); // On récupère la dimension n*p de la matrice : respectivement width et height

		assert(m = AllocMatrice(hauteur, largeur));

		for (i = 0; i < m->height; i++) {
			for (j = 0; j < m->width - 1; j++)
				fscanf(fichier, "%lf ", &m->M[i][j]);

			fscanf(fichier, "%lf\n", &m->M[i][m->width - 1]); // Permet de gérer le retour à la ligne pour la nouvelle ligne de la matrice							
		}
		fclose(fichier);
		return m;
	}
	else {
		printf("Le fichier n'a pas pu être ouvert\n");
		return NULL;
	}
}

Matrice *AllocMatrice(int height, int width) { // Ouvre un fichier.txt afin de remplir la structure Matrice	
	int i;
	Matrice *m = malloc(sizeof(*m));
	m->width = width;
	m->height = height;
	m->M = (double**)calloc(m->height, sizeof(double*)); // On alloue dynamiquement le tableau à doubles entrées en fonction de n et p

	for (i = 0; i < m->height; i++)
		m->M[i] = (double*)calloc(m->width, sizeof(double));
	return m;
}

int AfficherMatrice(Matrice *m) {
	int i, j;

	for (i = 0; i < m->height; i++) {
		printf("%d ", i + 1);
		for (j = 0; j < m->width; j++)
			printf("[%.2lf]", m->M[i][j]);

		printf("\n");
	}
	printf("\n");
	return 1;
}

int EcrireMatrice(char*path, Matrice *m) {
	int i, j;

	FILE *fichier = fopen(path, "w");
	fprintf(fichier, "%dx%d\n", m->height, m->width);
	if (fichier != NULL) {

		for (i = 0; i < m->height; i++) {
			for (j = 0; j < m->width - 1; j++)
				fprintf(fichier, "%.2lf", m->M[i][j]);

			fprintf(fichier, "%.2lf\n", m->M[i][m->width - 1]); // Permet de gérer le retour à la ligne pour la nouvelle ligne de la matrice							
		}
		fclose(fichier);
		return 1;
	}
	else {
		printf("Probleme dans l ecriture");
		return 0;
	}
}

void LibererMatrice(Matrice *m) {
	int i;
	for (i = 0; i < m->height; i++)
		free(m->M[i]);
	free(m->M);
	free(m);
}

double Trace(Matrice *m) {
	int i, j;
	double somme = 0;
	for (i = 0; i < m->height; i++) {
		for (j = 0; j < m->width; j++) {

			if (i == j)
				somme += m->M[i][j];
		}
	}
	return somme;
}

double Det(Matrice *m, int ligne) {
	int j;
	double determinant = 0;
	if ((m->height <= 1) && (m->width <= 1))
		return m->M[0][0];

	Matrice* prov = AllocMatrice(m->height - 1, m->width - 1);

	for (j = 0; j < m->width; j++) {
		Reduction(m, prov, ligne, j);
		determinant += PuissanceRec((-1), ligne + j, 1)*m->M[ligne][j] * Det(prov, ligne);
	}
	return determinant;
}

void Reduction(Matrice *m, Matrice *f, int ligne, int colonne) {
	int i, j, compteurL = 0, compteurC = 0;

	for (i = 0; i < m->height; i++) {

		if (i != ligne) {

			for (j = 0; j < m->width; j++) {

				if (j != colonne) {

					f->M[compteurL][compteurC] = m->M[i][j];
					compteurC++;
				}
			}
			compteurC = 0;
			compteurL++;
		}
	}
}

Matrice * Addition(Matrice *m, Matrice *n) {
	Matrice *p = AllocMatrice(m->height, m->width);
	int i, j;
	for (i = 0; i < m->height; i++) {
		for (j = 0; j < m->width; j++)
			p->M[i][j] = m->M[i][j] + n->M[i][j];
	}
	return p;

}

Matrice * Soustraction(Matrice *m, Matrice *n) {
	Matrice *p = AllocMatrice(m->height, m->width);
	int i, j;
	for (i = 0; i < m->height; i++) {
		for (j = 0; j < m->width; j++)
			p->M[i][j] = m->M[i][j] - n->M[i][j];
	}
	return p;
}

Matrice * ProduitExterne(Matrice *m, double s) {
	Matrice *p = m;
	int i, j;
	for (i = 0; i < m->height; i++) {
		for (j = 0; j < m->width; j++)
			p->M[i][j] = m->M[i][j] * s;
	}
	return p;
}

Matrice * ProduitInterne(Matrice *m, Matrice *n) {
	Matrice *p = AllocMatrice(m->height, n->width);
	int i, j, k;
	for (i = 0; i < m->height; i++) {
		for (j = 0; j < n->width; j++) {
			p->M[i][j] = 0;
			for (k = 0; k < m->width; k++)
				p->M[i][j] += m->M[i][k] * n->M[k][j];
		}
	}
	return p;
}

Matrice * Puissance(Matrice m, int n) {
	Matrice *p = &m;
	int i;
	for (i = 1; i < n; i++)
		p = ProduitInterne(p, &m);
	return p;
}

int PuissanceRec(int valeur, short n, int accu) {

	return (n == 0) ? accu : PuissanceRec(valeur, n - 1, accu*valeur);
}