#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef struct Matrice_s{
	
	int height;	   // Contient le nombre de lignes de la matrice
	int width;	   // Contient le nombre de colonnes de la matrice
	double **M; // Tableau contenant les coefficients de la matrice	
}Matrice;

Matrice *AllocMatrice(int width, int height); // Permet de charger une matrice de taille n*p à partir d'un fichier de configuration
Matrice *ChargerMatrice (char *path);
int EcrireMatrice (char*path, Matrice *m);
int AfficherMatrice(Matrice *m); // Permet d'afficher une matrice
int RechercherMax(Matrice *m,int r,int colonne);

void EchelonnerMatrice(Matrice *m); // Permet d'échelonner et réduire une matrice grâce à la méthode Gauss-Jordan
void LibererMatrice(Matrice *m); // Permet de libérer l'espace mémoire alloué à la matrice
double Trace (Matrice *m);
Matrice * Soustraire(Matrice*m,int i,double multiplicator,int r);
Matrice * DiviseLigne(Matrice *m,double diviseur,int ligne);
Matrice * Echanger(Matrice *m,int k,int r);
Matrice * Addition (Matrice *m,Matrice *n);
Matrice * Soustraction (Matrice *m,Matrice *n);
Matrice * ProduitExterne (Matrice *m,double s);
Matrice * ProduitInterne (Matrice *m,Matrice *n);
Matrice * Puissance (Matrice m,int n);

