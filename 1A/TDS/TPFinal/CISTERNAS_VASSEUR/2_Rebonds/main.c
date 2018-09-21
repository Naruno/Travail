#include "balle.h"

int main ( int argc, char** argv )
{	
	if(argc>1){	
		Balle info = chargerBalle(argv[1]);	// Charge la balle a partir de Balle.txt		
		float attenue=-0.9; // Coefficient d attenuation apres un choc contre un bord

		if(!sdl_startup())
			return -1;			
		fpsInit();
			
		do{ // Boucle pour mettre a jour en continue la simulation
		
			fpsStep();
			majPosition(&info,fpsGetDeltaTime()); // Mise a jour de la position
			if(info.position.x<BALL_RADIUS){ // On gère les collisions avec les bords
				info.position.x=BALL_RADIUS;				
				info.vitesse.x*=attenue;				
			}
			if(info.position.y<BALL_RADIUS){
				info.position.y=BALL_RADIUS;				
				info.vitesse.y*=attenue;
			}
			if(info.position.x>1-BALL_RADIUS){
				info.position.x=1-BALL_RADIUS;			
				info.vitesse.x*=attenue;				
			}
			if(info.position.y>1-BALL_RADIUS){
				info.position.y=1-BALL_RADIUS;				
				info.vitesse.y*=attenue;
			}				
			sdl_setBallPosition(info.position.x,info.position.y); // Mise à jour de la position de la balle
		}while(sdl_loop());
		sdl_clean();
	}
    return 0;
}