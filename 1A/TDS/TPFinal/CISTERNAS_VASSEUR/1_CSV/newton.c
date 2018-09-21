#include "balle.h"
int main(int argc, char **argv){
	
	if(argc>1){	
		Balle info = chargerBalle(argv[1]); 
		FILE* fichier = fopen(argv[2],"w"); // Ouverture d un fichier en mode ecriture
		if(fichier != NULL){ // Si le pointeur sur ficher est valide, on ecrit dans le fichier 
			float temps,dt=0.01;
			for(temps=0;temps<3;temps+=dt){ // Ecriture dans le fichier csv des positions x et y pour une augmentation de temps dt				
				fprintf(fichier," %.4f ; %.4f ; %.4f \n",temps,info.position.x,info.position.y);
				if(majPosition(&info,dt)==0){} // Test si majPosition renvoie bien 0
					
				else EXIT_FAILURE;						
			}
			fclose(fichier);
		}		
	}
	else
		printf("Il faut mettre les fichiers balle.txt et configuration.csv en argument de la ligne de commande !\n");		
	return 0;
}