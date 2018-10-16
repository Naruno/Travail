#pragma once
#ifndef GAUSS_H
#define GAUSS_H
#include "matrice.h"
int PivotGaussAuto(Matrice *mat);  // Permet d'�chelonner et r�duire une matrice gr�ce � la m�thode Gauss-Jordan
int RechercherMax(Matrice *m, int r, int colonne);
int Dilatation(Matrice *mat, int Li, double lambda);
int Transvection(Matrice*mat, int Li, int Lj, double lambda);
int Transposition(Matrice *mat, int Li, int Lj); //Transpose deux lignes en entrant des indices de matrices mathematiques
void PivotGaussManuel(Matrice *systeme);
void clean_stdin(void);
Matrice *Inverse(Matrice *mat);
#endif