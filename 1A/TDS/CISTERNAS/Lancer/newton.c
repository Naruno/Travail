#include "balle.h"
#include "math.h"
int main(int argc, char **argv){
	float tmp=0,angle=0;
	if(argc>1){	
		Balle info = chargerBalle(argv[1]);
		tmp=0;
		angle=0;
		
		for(int teta=0;teta<90;teta+=0.1){ // J'essaye de tester toutes les valeurs entre 0 et PI/2
			//Le vecteur V initiale est V0.x*cos(teta) V0.y*sin(teta)
			info.vitesse=ProdVect(info.vitesse,creerVect(cos(teta)*(float)(180/3.141592),sin(teta)*(float)(180/3.141592)));
			
			float temps,dt=0.01;
			for(temps=0;temps<3;temps+=dt){ // Ecriture dans le fichier csv des positions x et y pour une augmentation de temps dt		
		
				if(!majPosition(&info,dt)){} // Test si majPosition renvoie bien 0
					
				else EXIT_FAILURE;		
				printf("[%f]",info.position.x);
				if(info.position.x>tmp){
					tmp=info.position.x;
					angle=teta;
					printf("ok");
				}
								
			}
			//printf("%f %f",angle,tmp);
			info=chargerBalle(argv[1]);	
		}
		
	}
	printf("distance max : %f, pour un angle %f",tmp,angle);	
	return 0;
}