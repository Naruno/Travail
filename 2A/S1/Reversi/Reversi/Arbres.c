#include "Arbres.h"
#include "Reversi.h"

noeud* creerListe(char p_valeur[8][8], char a, char b) {
	
	noeud* tete = (noeud*)calloc(1, sizeof(*tete));
	
	if (!tete) {
		printf("Erreur lors de l'allocation de la tete de liste.\n");
		system("pause");
		exit(EXIT_FAILURE);
	}	
	copyTab(tete->m_valeur, p_valeur); 
	tete->m_suivant = NULL;
	tete->m_enfant = NULL;
	tete->m_coords[0] = a;
	tete->m_coords[1] = b;
	tete->m_nb_enfants = 0;
	return tete;
}

void libererListe(noeud * p_liste) {

	if (!p_liste) return;
	
	libererListe(p_liste->m_enfant);
	libererListe(p_liste->m_suivant);
	free(p_liste);	
}

noeud* ajoutTete(noeud* p_liste, char p_valeur[8][8], char a, char b) {
	
	noeud* nouveau = creerListe(p_valeur, a, b);

	if (!nouveau) {
		printf("Impossible d'inserer un noeud dans une liste vide ou Erreur d'allocation du nouvel noeud.\n");
		system("pause");
		exit(EXIT_FAILURE);
	}
	nouveau->m_suivant = p_liste;
	return nouveau;	
}

void afficherListe(noeud* p_liste) {

	if (!p_liste) return;
	
	afficheOthellier(p_liste->m_valeur);	
	afficherListe(p_liste->m_suivant);
}

void construction(noeud **tete, char profondeur, char joueur) {

	if (!tete || !(*tete) || !profondeur) return;	

	char papa[8][8], enfant[8][8], motif = (joueur % 2 == 0) ? NOIR : BLANC, a, b;
	copyTab(papa, (*tete)->m_valeur);

	for (a = 0; a < 8; a++) {
		for (b = 0; b < 8; b++) {
			if (legal(papa, a, b, motif)) {				
				copyTab(enfant, papa);
				enfant[a][b] = motif;
				majCouleur(enfant, a, b, motif);
				(*tete)->m_enfant = ajoutTete((*tete)->m_enfant, enfant, a, b);
			}
		}
	}
	construction(&((*tete)->m_enfant), profondeur - 1, joueur + 1);
	construction((&(*tete)->m_suivant), profondeur, joueur);
}

char MinMax(noeud **arbre, char joueur, char a, char b) {

	if (!arbre) {
		printf("ENORME PROBLEME D\'ARBRE !!! T_T\n");
		system("pause");
		exit(EXIT_FAILURE);
	}
	if (!((*arbre)->m_enfant)) {
		char scora[2];
		score((*arbre)->m_valeur, &scora, 0, 0);
		return scora[0] - scora[1];
	}
	char alpha = a, beta = b;
	noeud *tempo = (*arbre)->m_enfant;

	if (!(joueur % 2)) {
		while (tempo->m_suivant && tempo->m_enfant) {			
			beta = min(beta, MinMax(&(tempo->m_enfant), joueur + 1, alpha, beta));
			if (alpha >= beta) return alpha;
			tempo = tempo->m_suivant;
		}
		return beta;
	}
	else {
		while (tempo->m_suivant && tempo->m_enfant) {			
			alpha = max(alpha, MinMax(&(tempo->m_enfant), joueur + 1, alpha, beta));
			if (alpha >= beta) return beta;
			tempo = tempo->m_suivant;
		}
		return alpha;
	}	
	return 0;
}

char choixScore(noeud *p_liste, char p_joueur) {	
	
	if (!(p_liste->m_suivant)) 	return p_liste->m_score;
	
	p_liste->m_suivant->m_score = choixScore(p_liste->m_suivant,  p_joueur);
	return (!p_joueur) ? min(p_liste->m_score, p_liste->m_suivant->m_score) : max(p_liste->m_score, p_liste->m_suivant->m_score);		
}

void recherche(noeud *p_liste, char(*p_joueur)[2], char cible){

	if (!p_liste) {
		printf("GROS POBLEME\n");
		system("pause");
		exit(EXIT_FAILURE);
	}	
	if(p_liste->m_score != cible) recherche(p_liste->m_suivant, p_joueur, cible);
	
	(*p_joueur)[0] = p_liste->m_coords[0];
	(*p_joueur)[1] = p_liste->m_coords[1];	
}

void afficherCoords(noeud* p_liste) { printf("%d | %d\n", p_liste->m_coords[0], p_liste->m_coords[1]); }