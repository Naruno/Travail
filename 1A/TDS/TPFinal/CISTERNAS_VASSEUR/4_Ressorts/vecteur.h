#ifndef VECTEUR_H
#define VECTEUR_H
#include <stdio.h>
#include <stdlib.h>

// Strcture contenant les coordonnées x et y d'un vecteur
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

// Calcule la norme d un vecteur v
float normVect(Vecteur v);

// Rend la norme d un vecteur egale a 1
Vecteur normaliseVect(Vecteur v);

//Retourne la soustraction de 2 vecteurs 
Vecteur subVect(Vecteur v1, Vecteur v2);

#endif