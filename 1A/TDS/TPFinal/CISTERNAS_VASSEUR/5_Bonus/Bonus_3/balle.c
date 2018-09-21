#include <stdio.h>
#include <stdlib.h>
#include "decl.h"
#include <math.h>
#include "balle.h"
#include "vecteur.h"

Balle chargerBalle(char* chemin){
	Balle info;
	FILE *fichier= fopen(chemin,"r"); // Lecture des donnees du fichier balle.txt
		
		if(fichier != NULL){	    // On verifie que le pointeur sur fichier est valide	
			fscanf(fichier,"masse %f\n fCoef %f\nposition %f %f\nvitesse %f %f",
			&info.masse,&info.coeffriction,&info.position.x,&info.position.y,&info.vitesse.x,&info.vitesse.y); // Remplissage de la structure
			fclose(fichier);					   				   
		}
		else{
			printf("Impossible d'ouvrir le fichier");
			EXIT_FAILURE;
		}
			
	return info;	
}

int majPosition(Balle * balle, AttracteurList *pAttList, float dt){ // Met à jour la position de la balle avec le PFD en fonction des attracteurs

	if (balle==NULL)
		return -1;
	
	Vecteur attracteurs=creerVect(0,0);	 // Creation du vecteur somme des forces à l etat initial
	
	for(int i=0;i<NB_ATTRACTEURS;i++){
		
		Vecteur position=subVect(balle->position,pAttList->positionAttracteurs[i]); // Calcule de difference des positions de la balle et de l'astre i
		float distance=pow(normVect(position),2),magnitude; // Calcule du carré de la distance qui intervient dans la formule de la force
		
		if (distance!=0){
			magnitude=(-0.1)/distance;		// Calcule de la partie flotante de la formule de la force
			if (magnitude<-1) 
				magnitude=-0.5;   // Gere une vitesse trop elevee
				
		}
		else 
			magnitude=0;
			
		Vecteur u12=normaliseVect(position);// Calcule du vecteur U12 (normalise)
		
		Vecteur force=multScalVect(magnitude,u12); 
		Vecteur coefficient=multScalVect(pAttList->utiliseMoi[i],force); /* Application du coefficient utiliseMoi[i] à la force (0 ou 1) 
																		 * Si un astre a ete placé, utiliseMoi[i] vaut 1*/
		attracteurs=addVect(attracteurs,coefficient); //Addition successive des forces s appliquant a la balle		
	}			
	Vecteur acceleration=multScalVect(1/balle->masse,attracteurs); // Calcul de l acceleration
	balle->vitesse=addVect(balle->vitesse,multScalVect(dt,acceleration)); // Mise a jour de la vitesse
	balle->position=addVect(balle->position,multScalVect(dt,balle->vitesse)); // Mise a jour de la position
	return 0;
}

void initAttracteurList(AttracteurList * pAttrList){ //Initialise le tableau utiliseMoi à 0

	for(int i=0;i<NB_ATTRACTEURS;i++)
		pAttrList->utiliseMoi[i]=0;
}
