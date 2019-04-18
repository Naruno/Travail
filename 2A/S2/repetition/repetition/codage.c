#define _CRT_SECURE_NO_WARNINGS
#include "codage.h"

char codageBlanc(char* chemin) {
	FILE* blanc = fopen(chemin, "r");
	if (!blanc) {
		printf("Erreur d\'ouverture de fichier.\n");
		return 1;
	}
	unsigned char nouveau[50] = { 0 }, lettre = 0, detection = 0, espace = ' ', hashtag = '☺';

	strcat(nouveau, chemin);
	strcat(nouveau, "c");

	if (chemin[strlen(chemin) - 1] == 't') {	
		
		FILE* compresse = fopen(nouveau, "w");
		if (!compresse) {
			printf("Erreur de creation du fichier.\n");
			fclose(blanc);
			return 1;
		}		
		while (fread(&lettre, sizeof(char), 1, blanc)) {
			
			if (lettre == ' ') {
				detection++;				
				if (detection == 255) {
					fwrite("☺", sizeof(char), 1, compresse);
					fwrite(&detection, sizeof(char), 1, compresse);
					detection = 0;
					printf("stack\n");
				}
			}			
			else {
				if (detection > 2 ) {					
					fwrite(&hashtag, sizeof(char), 1, compresse);
					fwrite(&detection, sizeof(char), 1, compresse);
					detection = 0;
					fwrite(&lettre, sizeof(char), 1, compresse);
				}
				else {					
					for(char i = 0; i < detection; i++)
						fwrite(&espace, sizeof(char), 1, compresse);

					fwrite(&lettre, sizeof(char), 1, compresse);
					detection = 0;
				}						
			}
		}		
		fclose(compresse);
	}
	else {		
		FILE* decompresse = fopen("decompresse.txt", "w");
		if (!decompresse) {
			printf("Erreur de creation du fichier.\n");
			fclose(blanc);
			return 1;
		}
		while (fread(&lettre, sizeof(char), 1, blanc)) {

			if (lettre == '☺' && !detection) detection = 1;
			
			else {
				if (detection) {
					for (char i = 0; i < lettre; i++)	fwrite(&espace, sizeof(char), 1, decompresse);					
					detection = 0;
				}
				else fwrite(&lettre, sizeof(char), 1, decompresse);				
			}			
		}
		fclose(decompresse);
	}
	fclose(blanc);
	return 0;
}

char codageRLE(char* chemin) {

	FILE* blanc = fopen(chemin, "r");
	if (!blanc) {
		printf("Erreur d\'ouverture de fichier.\n");
		return 1;
	}
	unsigned char nouveau[50] = { 0 }, lettre = 0, detection = 0, hashtag = '☺', memoire = ' ', verif = 0, signe = 0;
	char nb_element = -1;

	strcat(nouveau, chemin);
	strcat(nouveau, "c");

	if (chemin[strlen(chemin) - 1] == 't') {
		liste* symboles = NULL;
		while (fread(&lettre, sizeof(char), 1, blanc)) {
			isIn(lettre, &symboles);
		}
		printList(symboles);
		
		FILE* compresse = fopen("testrle.txt", "w");
		//FILE* compresse = fopen(nouveau, "w");
		if (!compresse) {
			printf("Erreur de creation du fichier.\n");
			fclose(blanc);
			return 1;
		}
		fseek(blanc, 0, SEEK_SET);
		while (fread(&lettre, sizeof(char), 1, blanc)) {
			
			//printf("[%c]\n", lettre);
			addDetection(lettre, &symboles);
			verif = nbDetection(memoire, symboles);
			if (verif != 0 && memoire != lettre) {
				if (verif < 4) {
					for (int i = 0; i < verif; i++)
						fwrite(&memoire, sizeof(char), 1, compresse);

					zero(memoire, &symboles);
				}
				else {
					fwrite(&hashtag, sizeof(char), 1, compresse);
					fwrite(&verif, sizeof(char), 1, compresse);
					fwrite(&memoire, sizeof(char), 1, compresse);
					zero(memoire, &symboles);
					fwrite(&lettre, sizeof(char), 1, compresse);
				}
			}
			memoire = lettre;
		}
		fclose(compresse);
	}
	else {
		FILE* decompresse = fopen("decompresseRLE.txt", "w");
		if (!decompresse) {
			printf("Erreur de creation du fichier.\n");
			fclose(blanc);
			return 1;
		}
		while (fread(&lettre, sizeof(char), 1, blanc)) {

			if (nb_element != -1) signe = lettre;
			
			if (memoire == '☺') nb_element = lettre;
			
			if (lettre == '☺' && !detection) detection = 1;			

			
			if (detection && lettre != '☺') {
				for (char i = 0; i < nb_element; i++)	fwrite(&signe, sizeof(char), 1, decompresse);
				detection = 0;
			}
			else fwrite(&lettre, sizeof(char), 1, decompresse);
			
			memoire = lettre;
			nb_element = -1;
		}
		fclose(decompresse);
	}
	fclose(blanc);
	return 0;
}

liste* createListe(char symbole) {

	liste* nouveau = (liste*)calloc(1, sizeof(liste*));
	nouveau->m_detection = 0;
	nouveau->m_suivant = NULL;
	nouveau->m_symbole = symbole;
	return nouveau;
}

void isIn(char symbole, liste** l_symbole) {

	if (!(*l_symbole)) {
		*l_symbole = createListe(symbole);
		return;
	}

	
	if (symbole == (*l_symbole)->m_symbole) return;

	isIn(symbole, &(*l_symbole)->m_suivant);
}

void printList(liste* symboles) {

	if (!symboles) {
		printf("NULL\n");
		return;
	}
	printf("[%c]->", symboles->m_symbole);
	printList(symboles->m_suivant);
}

char nbDetection(char symbole, liste* l_symbole) {

	if (!symbole) {
		printf("GROS PROBLEME\n");
		return 0;
	}
	if (symbole == l_symbole->m_symbole) {
		//printf("detection [%c] -> %d\n", symbole, l_symbole->m_detection);
		return l_symbole->m_detection;
	}

	return nbDetection(symbole, l_symbole->m_suivant);
}

void addDetection(char symbole, liste** l_symbole) {

	if (!symbole || !(*l_symbole)) {
		//printf("GROS PROBLEME\n");
		return;
	}
	if (symbole == (*l_symbole)->m_symbole) {
		(*l_symbole)->m_detection++;
		//printf("Ajout !\n");
		return;
	}

	addDetection(symbole, &(*l_symbole)->m_suivant);
}

void zero(char symbole, liste** l_symbole) {

	if (!symbole) {
		printf("GROS PROBLEME\n");
		return ;
	}
	if (symbole == (*l_symbole)->m_symbole) {
		//printf("Remise a 0 de [%c]\n", symbole);
		(*l_symbole)->m_detection = 0;
		return;
	}

	zero(symbole, &(*l_symbole)->m_suivant);
}