#define _CRT_SECURE_NO_WARNINGS
#include "gauss.h"

int Dilatation(Matrice *mat, int Li, double lambda) { //lambda=1/pivot
	int j;
	for (j = 0; j < mat->width; j++) {

		mat->M[Li][j] /= lambda; //Diviseur = A[k,j]
	}
	return 1;
}

int Transposition(Matrice *mat, int Li, int Lj) {
	int j;
	double stock;
	for (j = 0; j < mat->width; j++) {

		stock = mat->M[Li][j];
		mat->M[Li][j] = mat->M[Lj][j];
		mat->M[Lj][j] = stock;

	}
	return 1;
}

int Transvection(Matrice*mat, int Li, int Lj, double lambda) {
	int j;
	for (j = 0; j < mat->width; j++)
		mat->M[Li][j] -= mat->M[Lj][j] * lambda;
	return 1;
}

int RechercherMax(Matrice *m, int r, int colonne) {
	int i, k = r + 1;
	double stock = fabs(m->M[r + 1][colonne]);

	for (i = r + 1; i < m->height; i++) {
		if (fabs(m->M[i][colonne]) > stock) {

			stock = fabs(m->M[i][colonne]);
			k = i;

		}
	}
	return k;
}

int PivotGaussAuto(Matrice *mat) {
	int i, j, k = 0, r = -1;
	for (j = 0; j < mat->width; j++) {

		if ((r >= mat->height - 1) || (r >= mat->width - 1))
			return 1;
		k = RechercherMax(mat, r, j);
		if (fabs(mat->M[k][j]) > 1e-5) {	// test non nul		
			r++;
			assert(Dilatation(mat, k, mat->M[k][j]));
			assert(Transposition(mat, k, r));
			for (i = 0; i < mat->height; i++) {
				if (i != r)
					assert(Transvection(mat, i, r, mat->M[i][j]));
			}
		}
	}
	return 1;
}

void clean_stdin(void) {
	int c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
}

void PivotGaussManuel(Matrice *systeme) {
	int suite = 1, Li, Lj;
	char choix = 'a';
	double lambda;
	while (suite == 1) {
		AfficherMatrice(systeme);
		printf("Transposer : t\nDilatation : d\nTransvection : u\nQue Faire ? ");
		clean_stdin();
		scanf("%c", &choix);
		clean_stdin();
		switch (choix) {

		case 't':
			printf("Ligne a transposer ? : ");
			scanf("%d", &Li);
			printf("Avel quelle ligne ? : ");
			scanf("%d", &Lj);
			Transposition(systeme, Li - 1, Lj - 1);
			AfficherMatrice(systeme);
			break;

		case 'd':
			printf("Dilater quelle ligne ? ");
			scanf("%d", &Li);
			printf("Dilater par quel reel ? ");
			scanf("%lf", &lambda);
			Dilatation(systeme, Li - 1, lambda);
			AfficherMatrice(systeme);
			break;

		case 'u':
			printf("Transvecter quelle ligne ? ");
			scanf("%d", &Li);
			printf("Transvecter avec quelle ligne ? ");
			scanf("%d", &Lj);
			printf("Ajouter a la ligne %d combien de fois la ligne %d ? ", Li, Lj);
			scanf("%lf", &lambda);
			Transvection(systeme, Li - 1, Lj - 1, -lambda);
			AfficherMatrice(systeme);
			break;
		}
		printf("Continuer les operations?\nOui : 1\nNon : 0\n");
		scanf("%d", &suite);
	}
}

Matrice *Inverse(Matrice *mat) {
	int i, j, k, jstock = mat->width;

	if (Det(mat, 0) != 0) {
		Matrice *inverse = AllocMatrice(mat->height, jstock);
		mat->width *= 2;
		for (i = 0; i < mat->height; i++) {
			mat->M[i] = realloc(mat->M[i], mat->width * sizeof(double));
			for (j = jstock; j < mat->width; j++) {
				if (i == j - jstock)
					mat->M[i][j] = 1;
				else
					mat->M[i][j] = 0;
			}
		}
		PivotGaussAuto(mat);
		for (i = 0; i < mat->height; i++) {
			for (j = jstock, k = 0; j < mat->width; j++, k++)
				inverse->M[i][k] = mat->M[i][j];
		}
		return inverse;
	}
	else {
		printf("Le determinant de la matrice est nulle, elle n\'est pas consequent pas inversible\n");
		return NULL;
	}
}