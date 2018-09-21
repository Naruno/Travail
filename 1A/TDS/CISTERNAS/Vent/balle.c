#include "balle.h"

Balle chargerBalle(char* chemin){
	
	Balle info;
	FILE *fichier= fopen(chemin,"r"); // Lecture des donnees du fichier balle.txt
		
		if(fichier != NULL){ // Si le pointeur sur ficher est valide, on lis le fichier pour remplire la structure Balle				
			fscanf(fichier,"masse %f\n fCoef %f\nposition %f %f\nvitesse %f %f\nvent %f",
			&info.masse,&info.coeffriction,&info.position.x,&info.position.y,&info.vitesse.x,&info.vitesse.y,&info.vent); // Remplissage de la structure Balle
			fclose(fichier);			
		}
		else{
			printf("Impossible d'ouvrir le fichier");
			EXIT_FAILURE;
		}
	return info;	
}

int majPosition(Balle *balle,float dt){ // Met à jour la position de la balle avec le PFD
	
	if (balle==NULL) // Securite contre un pointeur NULL
		return -1;
		
	Vecteur g=creerVect(0,-9.81); // Creation vecteur g		
	
	Vecteur poids=multScalVect(balle->masse,g); // Calcul du poids P=m*g	
	
	Vecteur frottements=multScalVect(-balle->coeffriction,balle->vitesse); // Calcul des forces de frottements
	
	Vecteur derive=creerVect(balle->vent,0);
	Vecteur vent=multScalVect(balle->coeffriction,derive);
	
	Vecteur somme=addVect(addVect(poids,frottements),vent); // Calcul de la somme des forces
	
	Vecteur acceleration=multScalVect((float)1/balle->masse,somme); // Calcul de l acceleration
	
	balle->vitesse=addVect(balle->vitesse,multScalVect(dt,acceleration)); // Mise a jour de la vitesse
	balle->position=addVect(balle->position,multScalVect(dt,balle->vitesse)); // Mise a jour de la position
	return 0;
}