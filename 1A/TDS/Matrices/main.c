#include "matrice.h"

int main(int argc, char **argv)
{
	int choix,n;
	double s;
	Matrice *matrice,*matrice2,*matrice3;
	if (argc>2){
		if(argc==3){		
			AfficherMatrice(ChargerMatrice(argv[1]));
			printf("Choix :\nTapez 1 pour Voir la Trace\nTapez 2 pour calculer le produit par un scalaire\nTapez 3 pour calculer la puissance n\n");
			printf("Tapez 4 pour Echelonnerla matrice\n");
			scanf("%d",&choix);
			switch(choix){
				
				case 1:
					matrice=ChargerMatrice(argv[1]);
					assert(matrice->height==matrice->width);
					printf("La trace de la matrice vaut : %.1lf\n",Trace(matrice));	
					LibererMatrice(matrice);
				break;
				
				case 2:
					matrice=ChargerMatrice(argv[1]);
					printf("Multiplier par quel scalaire ?\n");
					scanf("%lf",&s);
					matrice2=ProduitExterne(matrice,s);
					assert(AfficherMatrice(matrice));
					assert(EcrireMatrice(argv[2],matrice));	
					LibererMatrice(matrice);
				break;
				
				case 3:
					matrice=ChargerMatrice(argv[1]);
					printf("Elever a quelle puissance ?");
					scanf("%d",&n);
					matrice=Puissance(*matrice,n);
					assert(AfficherMatrice(matrice));
					assert(EcrireMatrice(argv[2],matrice));	
					LibererMatrice(matrice);
				break;	
				
				case 4:
					matrice=ChargerMatrice(argv[1]);
					EchelonnerMatrice(matrice);					
					AfficherMatrice(matrice);
					EcrireMatrice(argv[2],matrice);
					LibererMatrice(matrice);			
			}
		}
		else{			
			
			printf("Choix :\nTapez 1 pour Calculer la somme des matrices\nTapez 2 pour calculer la difference des matrices\nTapez 3 pour calculer le produit des 2 matrices\n");
			scanf("%d",&choix);
			printf("\n");
			switch(choix){
				
				case 1:
					matrice=ChargerMatrice(argv[1]);
					matrice2=ChargerMatrice(argv[2]);		
					assert((matrice->height==matrice2->height)&&(matrice->width==matrice2->width));
					matrice3=Addition(matrice,matrice2);
					assert(AfficherMatrice(matrice3));
					assert(EcrireMatrice(argv[3],matrice3));
					LibererMatrice(matrice);
					LibererMatrice(matrice2);
					LibererMatrice(matrice3);
				break;
				
				case 2:
					matrice=ChargerMatrice(argv[1]);
					matrice2=ChargerMatrice(argv[2]);						
					assert((matrice->height==matrice2->height)&&(matrice->width==matrice2->width));
					matrice3=Soustraction(matrice,matrice2);
					assert(AfficherMatrice(matrice3));
					assert(EcrireMatrice(argv[3],matrice3));
					LibererMatrice(matrice);
					LibererMatrice(matrice2);
					LibererMatrice(matrice3);
				break;
				
				case 3:
					matrice=ChargerMatrice(argv[1]);
					matrice2=ChargerMatrice(argv[2]);	
					assert(matrice->width==matrice2->height);
					matrice3=ProduitInterne(matrice,matrice2);
					assert(AfficherMatrice(matrice3));
					assert(EcrireMatrice(argv[3],matrice3));	
					LibererMatrice(matrice);
					LibererMatrice(matrice2);
					LibererMatrice(matrice3);
				break;					
			}
		}				
	}
	else{
		printf("Nombre d'arguments insuffisant\n");
	}			
	return 0;
}
