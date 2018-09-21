#include <stdio.h>
#include "vecteur.h"

typedef struct Balle_decl{
	
	float masse; 		// Kg
	float coeffriction;// (sans unite)
	Vecteur position; // En metres
	Vecteur vitesse; // En metres / sec
	Vecteur acceleration;    // En metres / sec / sec
	struct Balle_decl * ballePrecedente; // Pointeur sur la balle précédente
    struct Balle_decl * balleSuivante;	// Pointeur sur la balle suivante
}Balle;

// Retourne une structure Balle initalisée avec les valeurs du fichier de configuration
Balle chargerBalle(char* chemin);

 // Met a jour la position de la balle en appliquant le PFD
// Retourne -1 si balle est NULL (securite)
int majPosition(Balle * balle,float dt);