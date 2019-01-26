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