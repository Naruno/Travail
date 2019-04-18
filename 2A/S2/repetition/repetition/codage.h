#ifndef CODAGE
#define CODAGE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char codageBlanc(char* chemin);
char codageRLE(char* chemin);

typedef struct liste_s liste;

struct liste_s{

	char m_symbole;
	char m_detection;
	liste *m_suivant;

};


liste* createListe(char symbole);

void isIn(char symbole, liste **l_symbole);

void printList(liste* symboles);

char nbDetection(char symbole, liste* l_symbole);

void addDetection(char symbole, liste** l_symbole);

void zero(char symbole, liste** l_symbole);


#endif // !CODAGE