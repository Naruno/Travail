#define _CRT_SECURE_NO_WARNINGS
#include "matrice.h"
#include "gauss.h"

int main(int argc, char **argv)
{
	int choix, n;
	double s;
	Matrice *matrice, *matrice2, *matrice3;
	if (argc > 2) {
		if (argc == 3) {
			matrice = ChargerMatrice(argv[1]);
			AfficherMatrice(matrice);
			printf("Choix :\nTapez 1 pour Voir la Trace\nTapez 2 pour calculer le produit par un scalaire\nTapez 3 pour calculer la puissance n\n");
			printf("Tapez 4 pour Echelonnerla matrice\nTapez 5 pour Calculer le determinant de la matrice\nTapez 6 pour calculer l\'inverse de la matrice\n");
			scanf("%d", &choix);
			switch (choix) {

			case 1:
				if (matrice->height == matrice->width)
					printf("La trace de la matrice vaut : %.1lf\n", Trace(matrice));
				else {
					printf("La trace d\'une matrice asymetrique n\'existe pas\n");
					LibererMatrice(matrice);
				}
				break;

			case 2:
				printf("Multiplier par quel scalaire ?\n");
				scanf("%lf", &s);
				matrice2 = ProduitExterne(matrice, s);
				assert(AfficherMatrice(matrice));
				assert(EcrireMatrice(argv[2], matrice));
				LibererMatrice(matrice);
				break;

			case 3:

				printf("Elever a quelle puissance ?");
				scanf("%d", &n);
				matrice = Puissance(*matrice, n);
				assert(AfficherMatrice(matrice));
				assert(EcrireMatrice(argv[2], matrice));
				LibererMatrice(matrice);
				break;

			case 4:
				printf("Tapez 1 pour echelonner et reduire la matrice automatiquement\nTapez 2 pour echelonner la matrice pas a pas\n");
				scanf("%d", &choix);
				if (choix == 1) {

					assert((PivotGaussAuto(matrice)));
					AfficherMatrice(matrice);
					EcrireMatrice(argv[2], matrice);
					LibererMatrice(matrice);
				}
				if (choix == 2) {

					PivotGaussManuel(matrice);
				}
				break;

			case 5:

				if (matrice->height == matrice->width) {
					printf("Le déterminant de la matrice est %.2lf\n", Det(matrice, 0));
					EcrireMatrice(argv[2], matrice);
				}
				else {
					printf("On peut peut pas calculer le determinant d\'une matrice qui n\'est pas carree !\n");
					LibererMatrice(matrice);
				}
				break;

			case 6:

				if (matrice->height == matrice->width) {
					if (Det(matrice, 0) != 0) {
						Matrice* inverse = Inverse(matrice);
						AfficherMatrice(inverse);
						LibererMatrice(inverse);
					}
					else
						printf("Le determinant est nul, la matrice ne peut etre inversee\n");
				}
				else {
					printf("On ne peut inverser que des matrices carrees\n");
					LibererMatrice(matrice);
				}
				break;

			default:
				printf("Entrez un nombre valide");
			}
		}
		else {
			matrice = ChargerMatrice(argv[1]);
			matrice2 = ChargerMatrice(argv[2]);
			AfficherMatrice(matrice);
			AfficherMatrice(matrice2);
			printf("Choix :\nTapez 1 pour Calculer la somme des matrices\nTapez 2 pour calculer la difference des matrices\nTapez 3 pour calculer le produit des 2 matrices\n");
			scanf("%d", &choix);
			printf("\n");
			switch (choix) {

			case 1:
				if ((matrice->height == matrice2->height) && (matrice->width == matrice2->width)) {
					matrice3 = Addition(matrice, matrice2);
					assert(AfficherMatrice(matrice3));
					assert(EcrireMatrice(argv[3], matrice3));
					LibererMatrice(matrice);
					LibererMatrice(matrice2);
					LibererMatrice(matrice3);
				}
				else
					printf("On ne peut sommer que des matrices de memes dimensions\n");
				break;

			case 2:
				if ((matrice->height == matrice2->height) && (matrice->width == matrice2->width)) {
					matrice3 = Soustraction(matrice, matrice2);
					assert(AfficherMatrice(matrice3));
					assert(EcrireMatrice(argv[3], matrice3));
					LibererMatrice(matrice);
					LibererMatrice(matrice2);
					LibererMatrice(matrice3);
				}
				else
					printf("On ne peut soustraire que des matrices de memes dimensions\n");
				break;

			case 3:
				if (matrice->width == matrice2->height) {
					matrice3 = ProduitInterne(matrice, matrice2);
					assert(AfficherMatrice(matrice3));
					assert(EcrireMatrice(argv[3], matrice3));
					LibererMatrice(matrice);
					LibererMatrice(matrice2);
					LibererMatrice(matrice3);
				}
				else
					printf("On ne peut pas effectuer ce produit\n");
				break;
			}
		}
	}
	else {
		printf("Nombre d'arguments insuffisant\n");
	}
	return 0;
}
