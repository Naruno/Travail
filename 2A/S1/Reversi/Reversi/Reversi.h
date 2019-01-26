#ifndef REVERSI
#define REVERSI
#include <stdio.h>
#include <stdlib.h>

enum pion {VIDE = ' ', BLANC = 'O', NOIR = 'X'};
// Affiche le plateau de jeu passé en parametre. 
void afficheOthellier(char p_othellier[8][8]);
// Met à jour la partie en fonction des joueurs.
void majPartie(char p_othellier[8][8], char p_joueur, char p_profondeur);
// Dit si l'entrée utilisateur respecte les criteres de jeu.
char valide(char p_chaine);
// Converti un char en coordonnée de jeu.
char convertir(char p_lettre);
// Fonction réciproque de valide().
char convertirInverse(char p_chiffre);
// Dit si un coup peut être joué.
char legal(char p_othellier[8][8], char p_x, char p_y, char p_joueur);
// Met à jour les couleurs du plateau et retourne les pions mangés.
void majCouleur(char p_othellier[8][8], char p_x, char p_y, char p_joueur);
// Dit si au moins un coup est possible sur le plateau pour le joueur actuel.
char jouable(char p_othellier[8][8], char p_joueur);
// Calcul le score du plateau et le stocke dans le tableau p_joueur.
void score(char p_othellier[8][8], char (*p_joueur)[2], char p_fin, char p_mode);
// Copie un tableau.
void copyTab(char p_destination[8][8], char p_source[8][8]);
// Change la couleur de l'affichage.
void Color(int couleurDuTexte, int couleurDeFond);
#endif // !REVERSI