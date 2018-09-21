#ifndef VECTEUR_H
#define VECTEUR_H
#include <stdio.h>
#include <stdlib.h>
// Structure contenant les coordonnées x et y d'un vecteur
typedef struct Vecteur_decl{
	
	float x;
	float y;
}Vecteur;

// Retourne une structure Vecteur initialisee a (x,y)
Vecteur creerVect(float x,float y);

// Multiplie un scalaire avec un vecteur et retourne le resultat
Vecteur multScalVect(float s, Vecteur v);

// Additionne 2 vecteurs et retourne le resultat
Vecteur addVect(Vecteur v1, Vecteur v2);

#endif