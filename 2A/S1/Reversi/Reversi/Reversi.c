#define _CRT_SECURE_NO_WARNINGS
#include "Reversi.h"
#include "Arbres.h"
#include <string.h>
#include <conio.h>
#include <Windows.h>

void afficheOthellier(char p_othellier[8][8]) {

	char a, b;
	printf("  ");
	for (a = 'A'; a <= 'H'; a++) {
		printf(" %c ", a);
	}
	printf("\n");
	for (a = 0; a < 8; a++) {
		printf("%d ", a + 1);
		for (b = 0; b < 8; b++) {
			printf("[");
			(p_othellier[a][b] == NOIR) ? Color(4, 0) : Color(3, 0);
			if (p_othellier[a][b] == VIDE) {
				Color(15, 0);
			}
			printf("%c", p_othellier[a][b]);
			Color(15, 0);
			printf("]");
		}
		printf("\n");
	}
}

void majPartie(char p_othellier[8][8], char p_joueur, char p_profondeur) {

	char chaine[255], tmp[2] = { 0 }, coords[2], pos_x = 0, pos_y = 0, passage = 0;	
	noeud *tete = creerListe(p_othellier, -1,-1), *enfant;
	do {
		do {			
			if (p_joueur == NOIR) {
				printf("\nJoueur %c Inserez les coordonnees du pion a placer sur la grille. Exemple : C4.\n\n> ", p_joueur);
				scanf("%s", chaine);
			}
			else {		
				passage = 1;
				construction(&tete, p_profondeur, 1);

				enfant = tete->m_enfant;
				while (enfant->m_suivant) {
					enfant->m_score = MinMax(&enfant, 1, -100, 100);
					enfant = enfant->m_suivant;
				}											
				recherche(tete->m_enfant, &coords, choixScore(tete->m_enfant, 1));	
				goto victoire;				
			}					
			chaine[0] = tolower(chaine[0]);		
			// Tant que la chaine récupérées est mauvaise.
		} while (strlen(chaine) != 2 || !valide(chaine[0]));
		
		tmp[0] = chaine[1];
		pos_x = atoi(tmp) - 1;
		pos_y = convertir(chaine[0]);				
		
	// On test si le coup est jouable.	
	} while (!legal(p_othellier, pos_x, pos_y, p_joueur));			
	victoire:
	if (passage) {		
		libererListe(tete);
		p_othellier[coords[0]][coords[1]] = p_joueur;
		majCouleur(p_othellier, coords[0], coords[1], p_joueur);
		printf("\nJoueur O joue en %c%d !\n", toupper(convertirInverse(coords[1])), coords[0] + 1);
	}
	else {
		p_othellier[pos_x][pos_y] = p_joueur;
		majCouleur(p_othellier, pos_x, pos_y, p_joueur);
	}
}

char valide(char p_chaine) { return (p_chaine >= 97 && p_chaine <= 104) ? 1 : 0; }

char convertir(char p_lettre) {

	char compteur = 0;
	for (char a = 'a'; a < p_lettre; a++, compteur++) {}
	return compteur;
}

char convertirInverse(char p_chiffre) {

	char compteur = 'a';
	for (char a = 0; a < p_chiffre; a++, compteur++) {}
	return compteur;
}

char legal(char p_othellier[8][8], char p_x, char p_y, char p_joueur) {	
	
	char adversaire = (p_joueur == NOIR) ? BLANC : NOIR, a, b, tempo[8][8] = { 0 }, score_a[2], score_b[2];
	copyTab(tempo, p_othellier);

	if (p_othellier[p_x][p_y] == VIDE) {
		// Verifie les 8 cases adjacentes.
		for (a = -1; a <= 1; a ++) {	
			for (b = -1; b <= 1; b++) {
				if (p_othellier[p_x + a][p_y + b] == adversaire) {
					tempo[p_x][p_y] = p_joueur;
					majCouleur(tempo, p_x, p_y, p_joueur);

					score(p_othellier, &score_a, 0, 0);
					score(tempo, &score_b, 0, 0);

					if (p_joueur == NOIR)  return (score_b[0] > score_a[0] + 1) ? 1 : 0;					
					if (p_joueur == BLANC) return (score_b[1] > score_a[1] + 1) ? 1 : 0;					
				}
			}
		}				
	}		
	return 0;	
}

void copyTab(char p_destination[8][8], char p_source[8][8]) {
	char a, b;
	for (a = 0; a < 8; a++) 
		for (b = 0; b < 8; b++) 
			p_destination[a][b] = p_source[a][b];			
}

char jouable(char p_othellier[8][8], char p_joueur) {

	char a, b;
	for (a = 0; a < 8; a++) 
		for (b = 0; b < 8; b++) 
			if (legal(p_othellier, a, b, p_joueur)) return 1;				
	
	return 0;
}

void score(char p_othellier[8][8], char (*p_joueur)[2], char p_fin, char p_mode) {

	char a, b, score_VIDE = 0;
	(*p_joueur)[0] = 0, (*p_joueur)[1] = 0;
	for (a = 0; a < 8; a++) {
		for (b = 0; b < 8; b++) {

			if (p_othellier[a][b] == NOIR) 	(*p_joueur)[0]++;
			
			if (p_othellier[a][b] == BLANC) (*p_joueur)[1]++;
			
			if (p_othellier[a][b] == VIDE) 	score_VIDE++;			
		}
	}
	if (p_fin) {
		if ((*p_joueur)[0] > (*p_joueur)[1]) (*p_joueur)[0] += score_VIDE;
		
		else (*p_joueur)[1] += score_VIDE;
		
	}
	if (p_mode) {
		printf("\n");
		Color(4, 0);
		printf("X");
		Color(15, 0); 
		printf(" : %d\n", (*p_joueur)[0]);
		Color(3, 0);
		printf("O");
		Color(15, 0);
		printf(" : %d\n", (*p_joueur)[1]);
	}			
}

void majCouleur(char p_othellier[8][8], char p_x, char p_y, char p_joueur) {

	char adversaire = (p_joueur == NOIR) ? BLANC : NOIR, i, edition = 0, memoire = -1, motif = 0;
	
	// Manger vers la droite (->).
	for (i = -1; p_y + i >= 0; i--) {
		if (edition && i == memoire) {
			edition = 0, memoire = -1;
			break;
		}		
		motif = p_othellier[p_x][p_y + i];	
		if (motif == VIDE) 	break;
		
		if (motif == adversaire) {
			if (edition) p_othellier[p_x][p_y + i] = p_joueur;									
		}
		else edition = 1, memoire = i, i = 0;										
	}
	// Mangers vers le bas.
	for (i = -1; p_x + i >= 0; i--) {
		if (edition && i == memoire) {
			edition = 0, memoire = -1;
			break;
		}
		motif = p_othellier[p_x + i][p_y];
		if (motif == VIDE) 	break;
		
		if (motif == adversaire) {
			if (edition) p_othellier[p_x + i][p_y] = p_joueur;			
		}
		else edition = 1, memoire = i, i = 0;		
	}
	// Diagonale basse droite.
	for (i = -1; (p_x + i >= 0 && p_y + i >= 0); i--) {
		if (edition && i == memoire) {
			edition = 0, memoire = -1;
			break;
		}
		motif = p_othellier[p_x + i][p_y + i];
		if (motif == VIDE) break;
		
		if (motif == adversaire) {
			if (edition) p_othellier[p_x + i][p_y + i] = p_joueur;			
		}
		else edition = 1, memoire = i, i = 0;		
	}
	// Manger vers la gauche.
	for (i = -1; p_y - i < 8; i--) {
		if (edition && i == memoire) {
			edition = 0, memoire = -1;
			break;
		}
		motif = p_othellier[p_x][p_y - i];
		if (motif == VIDE) break;
		
		if (motif == adversaire) {
			if (edition) p_othellier[p_x][p_y - i] = p_joueur;			
		}
		else edition = 1, memoire = i, i = 0;		
	}
	// Manger vers le haut.
	for (i = -1; p_x - i < 8; i--) {
		if (edition && i == memoire) {
			edition = 0, memoire = -1;
			break;
		}
		motif = p_othellier[p_x - i][p_y];
		if (motif == VIDE) break;
		
		if (motif == adversaire) {
			if (edition) p_othellier[p_x - i][p_y] = p_joueur;			
		}
		else edition = 1, memoire = i, i = 0;		
	}
	for (i = -1; (p_x - i < 8 && p_y - i < 8); i--) {
		if (edition && i == memoire) {
			edition = 0, memoire = -1;
			break;
		}
		motif = p_othellier[p_x - i][p_y - i];
		if (motif == VIDE) break;
		
		if (motif == adversaire) {
			if (edition) p_othellier[p_x - i][p_y - i] = p_joueur;			
		}
		else edition = 1, memoire = i, i = 0;		
	}
	// Diagonale haute droite.
	for (i = -1; (p_x - i < 8 && p_y + i >= 0); i--) {
		if (edition && i == memoire) {
			edition = 0, memoire = -1;
			break;
		}
		motif = p_othellier[p_x - i][p_y + i];
		if (motif == VIDE) break;
		
		if (motif == adversaire) {
			if (edition) p_othellier[p_x - i][p_y + i] = p_joueur;			
		}
		else edition = 1, memoire = i, i = 0;		
	}
	for (i = -1; p_x + i >= 0 && p_y - i < 8; i--) {
		if (edition && i == memoire) {
			edition = 0, memoire = -1;
			break;
		}
		motif = p_othellier[p_x + i][p_y - i];
		if (motif == VIDE) break;
		
		if (motif == adversaire) {
			if (edition) p_othellier[p_x + i][p_y - i] = p_joueur;			
		}
		else edition = 1, memoire = i, i = 0;		
	}	
}

void Color(int couleurDuTexte, int couleurDeFond){
	HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}