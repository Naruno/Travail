#define _CRT_SECURE_NO_WARNINGS
#include "morse.h"
#include "affichage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define CLAIR "C:\\Users\\nicol\\source\\Programmation\\Travail\\2A\\S1\\ListeChaine\\Debug\\Morse.txt"
#define MORSE "C:\\Users\\nicol\\source\\Programmation\\Travail\\2A\\S1\\ListeChaine\\Debug\\Clair.txt"

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
	
	if (!(*p_pRoot)) {		
		return;
	}
	if (morse[0] == NULL) {	
		(*p_pRoot)->lettre = lettre;
		return;
	}
	if (morse[0] == '.') {	
		ajout_m(&((*p_pRoot)->m_gauche), morse + 1, lettre);
		
	}
	if (morse[0] == '-') {		
		ajout_m(&((*p_pRoot)->m_droit), morse + 1, lettre);
		
	}	
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

char morse_lettre(noeud_morse * noeud, char * morse) {

	if (!(morse[0])) {
		return noeud->lettre;
	}
	if (morse[0] == '.') {
		morse_lettre(noeud->m_gauche, morse + 1);
	}
	else {
		morse_lettre(noeud->m_droit, morse + 1);
	}
}

char * lettre_morse(char lettre) {
	pile_morse * pile = charger_liste();
	while (pile->lettre != lettre) {
		pile = pile->m_next;
	}
	return pile->morse;
}

noeud_morse * chargerMorse_plein() {
	noeud_morse * morse = creerNoeud_Morse(' ');
	pile_morse * pile = charger_liste();
	pile_morse * supprime = createPile_Morse(" ", ' ');
	morse = chargerMorse_Vide(morse, 5);
	while (pile) {
		pile = pop_m(pile, supprime);
		ajout_m(&morse, supprime->morse, supprime->lettre);
	}
	return morse;
}

char* convertisseur_morse_clair(char* path) {
	FILE* file = NULL;
	noeud_morse * morse = chargerMorse_plein();
	char message[1032] = "";
	char texte_clair[144][1032];
	char texte_morse[1032] = "";	
	int ctr = 0, j = 0, i;
	int taille;
	file = fopen(path, "r");
	if (!file) {
		printf("Erreur lors de l\'ouverture du fichier.\n");
		return;
	}	
	fseek(file, 0, SEEK_END);
	taille = ftell(file);
	fseek(file, 0, SEEK_SET);
	fread(texte_morse, taille, 1, file);
	fclose(file);
	printf("Morse : %s\n", texte_morse);
	
	taille = strlen(texte_morse);	
	for (i = 0; i <= taille; i++){
		// if space or NULL found, assign NULL into newString[ctr]
		if (texte_morse[i] == ' ' || texte_morse[i] == '\0'){
			texte_clair[ctr][j] = '\0';
			ctr++;  //for next word
			j = 0;    //for next word, init index to 0
		}
		else{
			texte_clair[ctr][j] = texte_morse[i];
			j++;
		}
	}
	for (i = 0; i < ctr; i++) {
		//printf("\"%s\"\n", texte_clair[i]);
		if (texte_clair[i] != ' ') {
			message[strlen(message)] = morse_lettre(morse,texte_clair[i]);
		}
		else {
			message[strlen(message)] = ' ';
		}		
	}
	printf("clair : %s\n", message);
	libererMorse(&morse);
	return message;
}

char * convertisseur_clair_morse(char* path) {
	FILE* file = NULL;	
	char message[1032] = "";
	char texte_clair[144][1032];
	char texte_morse[1032] = "";
	int ctr = 0, j = 0, i;
	int taille;
	file = fopen(path, "r");
	if (!file) {
		printf("Erreur lors de l\'ouverture du fichier.\n");
		return;
	}
	fseek(file, 0, SEEK_END);
	taille = ftell(file);
	fseek(file, 0, SEEK_SET);
	fread(texte_morse, taille, 1, file);
	fclose(file);
	printf("clair : %s\n", texte_morse);
	taille = strlen(texte_morse);	
	for (i = 0; i <= taille; i++) {
		// if space or NULL found, assign NULL into newString[ctr]
		if (texte_morse[i] == ' ' || texte_morse[i] == '\0') {
			texte_clair[ctr][j] = '\0';
			ctr++;  //for next word
			j = 0;    //for next word, init index to 0
		}
		else {
			texte_clair[ctr][j] = toupper(texte_morse[i]);
			j++;
		}
	}	
	for (i = 0; i < ctr; i++) {		
		for (j = 0; j < strlen(texte_clair[i]); j++) {			
			strcat(message, lettre_morse(texte_clair[i][j]));
			message[strlen(message)] = ' ';
		}		
		message[strlen(message)] = ' ';		
	}
	printf("morse : %s\n", message);
	return message;
}

void test_Morse() {
	int choix;
	printf("0 : Morse -> Clair\n1 : Clair -> Morse\n");
	scanf("%d", &choix);
	if (choix != 0 && choix != 1) {
		printf("Entrez 0 ou 1");
		return;
	}
	if (!choix) {
		char* texte_clair = convertisseur_morse_clair(CLAIR);
	}
	else {
		char* texte_morse = convertisseur_clair_morse(MORSE);
	}
	return;
}
