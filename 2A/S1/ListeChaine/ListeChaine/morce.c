#include "morse.h"
#include "affichage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

noeud_morse * creerNoeud_Morse(char lettre) {

	noeud_morse* noeud = (noeud_morse*)calloc(1, sizeof(*noeud));

	if (!noeud) {
		printf("Erreur lors de l'allocation de list ou node.\n");
		return NULL;
	}	
	
	noeud->lettre = lettre;
	noeud->m_gauche = NULL;
	noeud->m_droit = NULL;	
	return noeud;
}

void libererMorse(noeud_morse ** p_ppRoot) {

	if (!(*p_ppRoot)) {
		return;
	}
	libererMorse(&((*p_ppRoot)->m_gauche));
	libererMorse(&((*p_ppRoot)->m_droit));
	free(*p_ppRoot);
	*p_ppRoot = NULL;
	return;
}

int hauteur_m(noeud_morse * p_pRoot) {

	if (!p_pRoot || (!p_pRoot->m_gauche) && (!p_pRoot->m_droit)) {
		return 0;
	}
	int a = hauteur_m(p_pRoot->m_gauche);
	int b = hauteur_m(p_pRoot->m_droit);

	return (a > b) ? a + 1 : b + 1;
}

void afficher_noeud_m(noeud_morse * p_pRoot) {
	if (!p_pRoot) {
		return;
	}	
	printf("\"%c\"", p_pRoot->lettre);	
}

void afficher_Morse(noeud_morse * p_pRoot, int profondeur) {
	if (!p_pRoot) {
		return;
	}
	int i = 0;
	afficher_Morse(p_pRoot->m_droit, profondeur + 1);
	for (i = 0; i < profondeur; i++) {
		printf("    ");
	}
	afficher_noeud_m(p_pRoot);
	printf("\n");
	afficher_Morse(p_pRoot->m_gauche, profondeur + 1);
}

void affichage_propre_m(char* message, noeud_morse * p_pRoot) {
	int i, profondeur = hauteur_m(p_pRoot);
	print(message);

	for (i = 0; i < 4 * (profondeur + 1); i++) {
		printf("-");
	}
	printf("\n");
	afficher_Morse(p_pRoot, 0);
	for (i = 0; i < 4 * (profondeur + 1); i++) {
		printf("-");
	}
	printf("\n");
}

void ajout_m(noeud_morse ** p_pRoot, char* morse, char lettre) {
	printf("DEBUT\n");
	printf("\"%c\"\n", morse[0]);
	if (!(*p_pRoot)) {
		printf("MORT\n");
		return;
	}
	if (morse[0] == NULL) {
		printf("OK!\n");
		(*p_pRoot)->lettre = lettre;
		return;
	}
	if (morse[0] == '.') {
		printf("GAUCHE\n");
		ajout_m(&((*p_pRoot)->m_gauche), morse + 1, lettre);
		
	}
	if (morse[0] == '-') {
		printf("DROITE\n");
		ajout_m(&((*p_pRoot)->m_droit), morse + 1, lettre);
		
	}
	printf("FIN\n");
	
}
pile_morse* pop_stack_m(pile_morse** p_head) {

	if (!p_head) {
		return NULL;;
	}
	pile_morse* tmp = *p_head;
	*p_head = (*p_head)->m_next;
	tmp->m_next = NULL;
	return tmp;
}

pile_morse* createPile_Morse(char* chaine, char lettre) {
	// Cette fonction initialise une liste avec un premier node egal à 0.	
	pile_morse* noeud = (pile_morse*)calloc(1, sizeof(*noeud));

	if (!noeud) {
		printf("Erreur lors de l'allocation de list ou node.\n");
		exit(EXIT_FAILURE);
	}
	noeud->morse = chaine;
	noeud->lettre = lettre;
	noeud->m_next = NULL;	
	return noeud;
}

pile_morse* addLast_m(pile_morse* p_pRoot, char* chaine, char lettre) {
	// Cette fonction ajoute un élément en fin de liste de manière récursive.	

	if (!p_pRoot) {
		return createPile_Morse(chaine, lettre);
	}
	p_pRoot->m_next = addLast_m(p_pRoot->m_next, chaine, lettre);
	return p_pRoot;
}

pile_morse* pop_m(pile_morse* p_pRoot, pile_morse* save) {
	// Cette fonction supprime un élément en début de liste.
	if (!p_pRoot) {
		printf("Impossible de supprimer une élément d'une liste vide.\n");
		exit(EXIT_FAILURE);
	}
	else {
		pile_morse* aSupprimer = p_pRoot;	
		save->lettre = p_pRoot->lettre;
		save->morse = p_pRoot->morse;
		p_pRoot = p_pRoot->m_next;
		free(aSupprimer);
		return p_pRoot;
	}
}

void printPile_m(pile_morse* p_pRoot) {
	// Cette fonction affiche une liste.
	if (!p_pRoot) {
		printf("NULL\n");
		return;
	}	
	printf("%c -> ", p_pRoot->lettre);
	printPile_m(p_pRoot->m_next);	
}

pile_morse * charger_liste() {

	pile_morse * pile = createPile_Morse(".", 'E');

	pile = addLast_m(pile, "-", 'T');
	pile = addLast_m(pile, "..", 'I');
	pile = addLast_m(pile, ".-", 'A');
	pile = addLast_m(pile, "-.", 'N');
	pile = addLast_m(pile, "--", 'M');
	pile = addLast_m(pile, "...", 'S');
	pile = addLast_m(pile, "..-", 'U');
	pile = addLast_m(pile, ".-.", 'R');
	pile = addLast_m(pile, ".--", 'W');
	pile = addLast_m(pile, "-..", 'D');
	pile = addLast_m(pile, "-.-", 'K');
	pile = addLast_m(pile, "--.", 'G');
	pile = addLast_m(pile, "---", 'O');
	pile = addLast_m(pile, "....", 'H');
	pile = addLast_m(pile, "...-", 'V');
	pile = addLast_m(pile, "..-.", 'F');
	pile = addLast_m(pile, ".-..", 'L');
	pile = addLast_m(pile, ".--.", 'P');
	pile = addLast_m(pile, ".---", 'J');
	pile = addLast_m(pile, "-...", 'B');
	pile = addLast_m(pile, "-..-", 'X');
	pile = addLast_m(pile, "-.-.", 'C');
	pile = addLast_m(pile, "-.--", 'Y');
	pile = addLast_m(pile, "--..", 'Z');
	pile = addLast_m(pile, "--.-", 'Q');

	pile = addLast_m(pile, ".....", '5');
	pile = addLast_m(pile, "....-", '4');
	pile = addLast_m(pile, "...--", '3');
	pile = addLast_m(pile, "..---", '2');
	pile = addLast_m(pile, ".-.-.", '+');
	pile = addLast_m(pile, ".----", '1');
	pile = addLast_m(pile, "-....", '6');
	pile = addLast_m(pile, "-...-", '=');
	pile = addLast_m(pile, "-..-.", '/');
	pile = addLast_m(pile, "--...", '7');
	pile = addLast_m(pile, "---..", '8');
	pile = addLast_m(pile, "----.", '9');
	pile = addLast_m(pile, "-----", '0');

	return pile;
}

noeud_morse * chargerMorse_Vide(noeud_morse * noeud, int profondeur) {

	if (!profondeur) {
		return NULL;
	}
	else {
		noeud->m_gauche = creerNoeud_Morse(' ');
		chargerMorse_Vide(noeud->m_gauche, profondeur - 1);
		noeud->m_droit = creerNoeud_Morse(' ');
		chargerMorse_Vide(noeud->m_droit, profondeur - 1);		
	}
	return noeud;
}

void test_Morse() {

	noeud_morse * morse = creerNoeud_Morse(' ');	
	pile_morse * pile = charger_liste();
	pile_morse * supprime = createPile_Morse(" ", ' ');
	morse = chargerMorse_Vide(morse, 5);

	while (pile) {
		pile = pop_m(pile, supprime);
		ajout_m(&morse, supprime->morse, supprime->lettre);
	}
	
	//printPile_m(pile);	
	//printPile_m(supprime);
	
	
	
	
	affichage_propre_m("arbre de test\n", morse);
	
	
	return;
}