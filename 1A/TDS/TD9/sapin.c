#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char **argv){
	srand(time(NULL));
	int hauteur_s,hauteur_p,largeur_p,proportion,compteur=0;
	if (argc<2)
		return EXIT_FAILURE;
	else{
		FILE *pfile=NULL;
		char* path=argv[1];
		pfile=fopen(path,"r");
		if (pfile!=NULL){
			fscanf(pfile,"%d %d %d %d",&hauteur_s,&hauteur_p,&largeur_p,&proportion);				
			
			for(int i=0;i<hauteur_s;i++){				
				for (int j=0;j<hauteur_s-i;j++)
					printf(" ");
				for (int k=0;k<1+2*i;k++){
					if((rand()%2>0.5) && compteur<(float)((proportion)*6)/5){
						printf("o");
						compteur++;
					}
					else
						printf("*");					
				}
				printf("\n");								
			}
			for (int j=0;j<hauteur_p;j++){
				for (int i=0;i<hauteur_s*2-1;i++){
					if(i<hauteur_s-(largeur_p/2) || i>hauteur_s+(largeur_p/2))
						printf(" ");
					else 
						printf("|");
				}
				printf("\n");
			}			
		}
		else{
			printf("Le fichier n a pas pu etre ouvert\n");
			return EXIT_FAILURE;
		}				
	}					
	return 0;
}