#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "sdl_stuff.h"
#include "vecteur.h"
#include "balle.h"
#include "decl.h"
#include "fpstimer.h"

Balle gBalleTab[NB_BALLES];
AttracteurList gAttractList;

void clicSouris(float x, float y) // fonction appellée lorsque l'on appuie avec le bouton gauche de la souris
{
    // NB : une variable locale declaree static ne perd pas sa valeur entre deux appels a la fonction
    // son initialisation est effectué au tout premier appel de la fonction
    // on s'en sert ici pour savoir quel attracteur on est en train de positioner
    static int attracteurCurrent = 0 ; 
    gBalleTab[NB_BALLES-1].position = creerVect(x,y); // Initialise le vecteur position de la structure balle avec le vecteur (x,y)
    // gere les position de la liste des attracteurs 
    gAttractList.utiliseMoi[attracteurCurrent]=1; // Quand un attracteur est pose, on l'indique par un 1 dans utiliseMoi a l'indice AttracteurCurrent
    gAttractList.positionAttracteurs[attracteurCurrent]=creerVect(x,y); // Creer le vecteur position de l'attracteur
    
    sdl_setAttracteurPosition(attracteurCurrent,x,y); // Positionne l'attracteur
    attracteurCurrent ++;
    attracteurCurrent %=NB_ATTRACTEURS; // Empeche attracteurCurrent de depasser NB_ATTRACTEURS
}



int main ( int argc, char** argv )
{
     if(argc>1)
     {
        fpsInit();
        
        if(!sdl_startup())
        {
            return -1;
        }
        
        Balle info = chargerBalle(argv[1]); // On charge une balle
        initAttracteurList(&gAttractList); // Initialise la structure AttracteurList a 0
       
        for (int i=0; i<NB_BALLES; i++) // On initialise les 25 balles 
        {
            gBalleTab[i]=info;
        }
       
        for(int i=0; i<NB_BALLES; i++) // On relie les balles entre elles en verifiant que la balle precedente et suivante existe bien
        {
            if (i!=0)
                gBalleTab[i].ballePrecedente=&gBalleTab[i-1];
            if (i!=NB_BALLES-1)
                gBalleTab[i].balleSuivante=&gBalleTab[i+1];
        }

        do // Program main loop
        {
            fpsStep();
            
            for(int i=0; i<NB_BALLES; i++) // Mise a jour des NB_BALLES
            {
                majPosition(&gBalleTab[i],&gAttractList, fpsGetDeltaTime()); // Mise a jour de la position de la balle 
                // Les "if" suivants gerent les collisions avec les bords
                if (gBalleTab[i].position.x<BALL_RADIUS)
                {
                    gBalleTab[i].position.x=BALL_RADIUS;
                    gBalleTab[i].vitesse.x*=info.attenuation;
                }
                if (gBalleTab[i].position.y<BALL_RADIUS)
                {
                    gBalleTab[i].position.y=BALL_RADIUS;
                    gBalleTab[i].vitesse.y*=info.attenuation;
                }
                if (gBalleTab[i].position.x>1-BALL_RADIUS)
                {    
                    gBalleTab[i].position.x=1-BALL_RADIUS;
                    gBalleTab[i].vitesse.x*=info.attenuation;
                }
                if (gBalleTab[i].position.y>1-BALL_RADIUS)
                {
                    gBalleTab[i].position.y=1-BALL_RADIUS;
                    gBalleTab[i].vitesse.y*=info.attenuation;
                }
                
                sdl_setBallPosition(i,gBalleTab[i].position.x,gBalleTab[i].position.y); // Affiche la balle i avec les positions mises a jour
            }
        } 
        while(sdl_loop()); // End main loop
    
        sdl_clean();
     }
    return 0;
}
