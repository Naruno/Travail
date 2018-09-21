#include <unistd.h>
#include "sdl_stuff.h"
#include "decl.h"
#include "fpstimer.h"
#include "balle.h"

Balle gBalleTab[NB_BALLES];

void dragSouris(float x, float y){ // Fonction appellee lorsque le bouton de la souris est maintenu
									
    gBalleTab[NB_BALLES-1].position=creerVect(x,y); // Initialise le vecteur position de la structure balle avec le vecteur (x,y)    
}

int main ( int argc, char** argv ){
	
	if(argc>1){		
		fpsInit();
		
		if(!sdl_startup()) 
			return -1;
		
		Balle info = chargerBalle(argv[1]); // On charge une balle
		float attenue=-0.9;			
		
		for(int i=0;i<NB_BALLES;i++){ // On initialise les 25 balles
			gBalleTab[i]=info;						
		}
			
		for(int i=0;i<NB_BALLES;i++){ // On relie les balles entre elles en verifiant que la balle precedente ou suivante existe bien			
			if (i!=0)	
				gBalleTab[i].ballePrecedente=&gBalleTab[i-1];
			
			if (i!=NB_BALLES-1)	
				gBalleTab[i].balleSuivante=&gBalleTab[i+1];
		}		
		do{ // Program main loop		
			fpsStep();							
			for(int i=0; i<NB_BALLES; i++){	// Mise a jour des NB_BALLES						
				majPosition(&gBalleTab[i],fpsGetDeltaTime()); 
				
				if(gBalleTab[i].position.x<BALL_RADIUS){ // On gère les collisions avec les bords
					gBalleTab[i].position.x=BALL_RADIUS;				
					gBalleTab[i].vitesse.x*=attenue;				
				}
				if(gBalleTab[i].position.y<BALL_RADIUS){
					gBalleTab[i].position.y=BALL_RADIUS;				
					gBalleTab[i].vitesse.y*=attenue;
				}
				if(gBalleTab[i].position.x>1-BALL_RADIUS){
					gBalleTab[i].position.x=1-BALL_RADIUS;			
					gBalleTab[i].vitesse.x*=attenue;				
				}
				if(gBalleTab[i].position.y>1-BALL_RADIUS){
					gBalleTab[i].position.y=1-BALL_RADIUS;				
					gBalleTab[i].vitesse.y*=attenue;
				}		
				sdl_setBallPosition(i,gBalleTab[i].position.x,gBalleTab[i].position.y); // Afficher la balle i avec les positions mises a jour
			}
		}while(sdl_loop()); // End main loop		
		sdl_clean();		
	}
    return 0;
}