#ifndef MATRICE_H
#define MATRICE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct Matrice_s {

	int height;	   // Contient le nombre de lignes de la matrice
	int width;	   // Contient le nombre de colonnes de la matrice
	double **M; // Tableau contenant les coefficients de la matrice	
}Matrice;

Matrice *AllocMatrice(int width, int height); // Permet de charger une matrice de taille n*p à partir d'un fichier de configuration
Matrice *ChargerMatrice(char *path);

int EcrireMatrice(char*path, Matrice *m);
int AfficherMatrice(Matrice *m); // Permet d'afficher une matrice
int PuissanceRec(int valeur, short n, int accu);
void LibererMatrice(Matrice *m); // Permet de libérer l'espace mémoire alloué à la matrice
double Trace(Matrice *m);
double Det(Matrice *m, int ligne);

Matrice * Addition(Matrice *m, Matrice *n);
Matrice * Soustraction(Matrice *m, Matrice *n);
Matrice * ProduitExterne(Matrice *m, double s);
Matrice * ProduitInterne(Matrice *m, Matrice *n);
Matrice * Puissance(Matrice m, int n);
void Reduction(Matrice *m, Matrice *f, int ligne, int colonne);
Matrice *Inverse(Matrice *mat);


#endif