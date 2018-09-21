#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "balle.h"
#include "vecteur.h"
#include "sdl_stuff.h"
#include "time.h"
#include "decl.h"
#include "fpstimer.h"
float total=0;
float interieur=0;
float calculs=0;
float tempo=0;
AttracteurList gAttractList;

// fonction appellée lorsque l'on appuie avec le bouton gauche de la souris
void clicSouris(float x, float y){    
    static int attracteurCurrent = 0 ;

    //Met à jour la position des planètes dans la structure
	gAttractList.positionAttracteurs[attracteurCurrent] = creerVect(x,y);
	//Met à jour le nombre de planète dans la structure
	gAttractList.utiliseMoi[attracteurCurrent]=1;
	
	sdl_setAttracteurPosition(attracteurCurrent,x,y);
	attracteurCurrent ++;
	attracteurCurrent %=NB_ATTRACTEURS;
}

int main ( int argc, char** argv ){
	if (argc>1){	
		
		Balle info;
		initAttracteurList(&gAttractList);		
		info = chargerBalle(argv[1]);

		if(!sdl_startup())
		return -1;

		fpsInit();
		// boucle pour mettre a jour en continue la simulation

		//Variable du minuteur
		unsigned int minutes=0;
		unsigned int secondes=0;
		unsigned int milisecondes=0;
		unsigned int duree=0,temps_restant=0;

		clock_t x_startTime,compteur_t;
		duree=15;  //Temps en sec	 
		x_startTime=clock();  
		temps_restant=duree-secondes;   
	
		do{
				
				if (temps_restant>0){
					
				fpsStep();			
			
				compteur_t=clock(); // update timer difference
				milisecondes=compteur_t-x_startTime;
				secondes=(milisecondes/(CLOCKS_PER_SEC))-(minutes*60);
				minutes=(milisecondes/(CLOCKS_PER_SEC))/60;				
				temps_restant=duree-secondes; // subtract to get difference 			

					//Calcul des forces selon la info, les planètes, le temps
				majPosition(&info, &gAttractList, fpsGetDeltaTime());				

				// On empêche la info de dépassé la fenêtre
				if (info.position.x <= BALL_RADIUS){
					info.vitesse.x=(-1)*info.vitesse.x;
					info.position.x = BALL_RADIUS;
				}

				if (info.position.x>=1-BALL_RADIUS){
					info.vitesse.x=(-1)*info.vitesse.x;
					info.position.x = 1-BALL_RADIUS;
				}

				if(info.position.y<=BALL_RADIUS){
					info.vitesse.y=(-1)*info.vitesse.y;
					info.position.y=BALL_RADIUS;
				}

				if(info.position.y>=1-BALL_RADIUS){
					info.vitesse.y=(-1)*info.vitesse.y;
					info.position.y=1-BALL_RADIUS;
				}		
				total+=1;						
						
				//Si la balle entre dans la cible
				if(info.position.y>=0.40){					
					if(info.position.y<=0.70){						
						if(info.position.x>=0.40){							
							if (info.position.x<=0.70)							
								interieur = interieur +1; // Nombre de calcul réalisés par la machine pendant que la balle était dans la cible						
						}
					}
				}			
				sdl_setBallPosition(info.position.x,info.position.y);
			}
			else
			break;
		}
		while(sdl_loop());		
		calculs = (interieur/total)*100;
		//calculs : nombre de calcules fait par la machine à l'intérieur du carré / nombre de calcul en tout

		char a='%';
		printf("%.1f%c de presence sur la cible\n",calculs,a);
		sdl_clean();
	}
	return 0;
}
