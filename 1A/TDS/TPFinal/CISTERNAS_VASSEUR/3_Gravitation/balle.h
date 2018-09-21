#include <stdio.h>
#include "vecteur.h"
#include "decl.h"

typedef struct Balle_decl{
	
	float masse; 		 // Kg
	float coeffriction; // Sans unite)
	Vecteur position;  // En metres
	Vecteur vitesse;  // En metres / sec
	Vecteur acceleration; // En metres / sec / sec
}Balle;

typedef struct AttracteurList_decl{ // Liste contenant les informations relatives aux attracteurs
	
	Vecteur positionAttracteurs[NB_ATTRACTEURS]; // Enregistre les positions des attracteurs
	int utiliseMoi[NB_ATTRACTEURS]; 			// Gere le nombre d attracteurs presents
}AttracteurList;

// Retourne une structure Balle initalisée avec les valeurs du fichier de configuration
Balle chargerBalle(char* chemin);

// Met a jour la position de la balle en appliquant le PFD
// Retourne -1 si balle est NULL (securite)
int majPosition(Balle * balle, AttracteurList *pAttList, float dt);

// Initialise la structure AttracteurList
void initAttracteurList(AttracteurList * pAttrList);