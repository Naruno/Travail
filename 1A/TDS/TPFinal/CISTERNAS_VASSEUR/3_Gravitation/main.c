#include "decl.h"
#include <unistd.h>
#include "sdl_stuff.h"
#include "fpstimer.h"
#include "balle.h"

AttracteurList gAttractList;

void clicSouris(float x, float y) // Fonction appellée lorsque l'on appuie avec le bouton gauche de la souris
{
    // NB : une variable locale declaree static ne perd pas sa valeur entre deux appels a la fonction
    // son initialisation est effectué au tout premier appel de la fonction
    // on s'en sert ici pour savoir quel attracteur on est en train de positioner
    static int attracteurCurrent = 0 ; 
    gAttractList.utiliseMoi[attracteurCurrent]=1; // Quand un attracteur est positionné on l indique par un 1 dans utiliseMoi a l indice attracteurCurrent
	gAttractList.positionAttracteurs[attracteurCurrent]=creerVect(x,y); // Creer le vecteur position l attracteur
    sdl_setAttracteurPosition(attracteurCurrent,x,y); // Positionne l attracteur
    attracteurCurrent ++;	
    attracteurCurrent %=NB_ATTRACTEURS; // Empeche attracteurCurrent de depasser NB_ATTRACTEURS
}
int main ( int argc, char** argv )
{
    if(argc>1){
		Balle info=chargerBalle(argv[1]); // Charge la balle a partir de Balle.txt
		float attenue=-0.7; // Coefficient d attenuation apres un choc contre un bord
		initAttracteurList(&gAttractList); // Initialise la structure AttracteurList a 0
		if(!sdl_startup())
			return -1;
		
		fpsInit();		
		do // Program main loop
		{
			fpsStep();

			majPosition(&info,&gAttractList,fpsGetDeltaTime()); // Mise a jour de la position de la balle avec les attracteurs
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

		}while(sdl_loop()); // End main loop
		
		sdl_clean();	
	}
    return 0;
}
