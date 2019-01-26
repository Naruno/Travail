#define _CRT_SECURE_NO_WARNINGS
#include "Reversi.h"
#include "Arbres.h"

int main() {	
	char tour = 0, compteur = 64, joueur, adversaire, othellier[8][8] = { VIDE }, i, j, profondeur, scora[2];
	int choix;
	for (i = 0; i < 8; i++) 
		for (j = 0; j < 8; j++) 
			othellier[i][j] = VIDE;		
	
	// On initialise la première croix de pions.
	othellier[3][3] = BLANC;
	othellier[4][4] = BLANC;
	othellier[3][4] = NOIR;
	othellier[4][3] = NOIR;

	// Récupère la profondeur.
	do {
		system("cls");
		printf("Bienvenu dans Reversi ! Vous allez jouer contre une IA, veuillez selectionner son niveau :\n\nFacile : \t1\nMoyen : \t2\nDifficile : \t3\n\nChoix : ");
		scanf("%d", &choix);
		getchar();
		if (choix == 1 || choix == 2 || choix == 3)	break;		
	} while(1);
	system("cls");
	if (choix) profondeur = 2;
	if (choix == 2) profondeur = 4;
	if (choix == 3) profondeur = 6;

	// La boucle de jeu.
	while (compteur > 0) {
		joueur = (!(tour % 2)) ? NOIR : BLANC;
		adversaire = (!(tour % 2)) ? BLANC : NOIR;	

		afficheOthellier(othellier);
		// Affiche le score à chaque tour.
		score(othellier, &scora, 0, 1);
		majPartie(othellier, joueur, profondeur);
	
		if (!jouable(othellier, adversaire)) {
			printf("%c ne peut pas jouer.\n", adversaire);
			tour++;
		}
		if(!jouable(othellier, adversaire) && !jouable(othellier, joueur)) {
			afficheOthellier(othellier);
			score(othellier, &scora, 1, 1);
			break;
		}		
		compteur--;	
		tour++;	
	}	
	system("pause");
	return 0;
}