#ifndef CHAINE
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

int longueurChaine(char *chaine) {

	if (!chaine) {
		printf("La chaine n'est pas valide\n");
		return 0;
	}
	int i = 0;
	while (chaine[i] != NULL) {
		i++;
	}
	//printf("%s fait %d characteres\n", chaine, i);
	return i;
}

int longueurChaineRec(char *chaine, int i) {
	
	if (!chaine[i]) {
		printf("%s fait %d characteres\n", chaine, i);
		return i;
	}
	else {
		longueurChaineRec(chaine, i + 1);
	}
}

char* copieChaine(char* chaine) {
	
	int taille = longueurChaineRec(chaine, 0), i = 0;	
	char* copie = (char*)calloc(taille+1, sizeof(char));
	if (!copie) {
		printf("Erreur lors de l'allocation memoire de la chaine copie\n");
		return NULL;
	}
	for (i = 0; i <= taille ; i++) {
		
		copie[i] = chaine[i];	    
	}
	copie[taille] = '\0';
	return copie;
}

void copieChaineRec(char* chaine, char* copie) {
	copie[0] = chaine[0];
	if (!chaine[0]) {
		return;
	}
	else {
		copieChaineRec(chaine + 1, copie + 1);	
	}
}

int compareChaine(char* chaine, char* chaine2) {

	int taille = longueurChaine(chaine) + 1, i = 0;
	for (i = 0; i < taille; i++) {

		if (chaine[0] != chaine2[0]) {
			return 0;
		}		
		return 1;
	}
}
int compareChaineRec(char* chaine, char* chaine2) {

	if (!chaine[0] && !chaine2[0]) {
		return 1;
	}
	if (chaine[0] != chaine2[0] || !chaine[0] || !chaine[0]) {
		return 0;
	}
	else {
		compareChaineRec(chaine + 1, chaine2 + 1);
	}
}

char* inverserChaine(char* chaine) {
	int taille = longueurChaine(chaine), i = 0;

	char* inverse = (char*) calloc(taille + 1, sizeof(char));
	if (!inverse) {
		printf("Erreur lors de l'allocation memoire de la chaine inverse\n");
		return NULL;
	}

	for (i = 0; i < taille; i++) {	
		inverse[i] = chaine[taille - i - 1];		
	}
	inverse[taille] = '\0';	
	return inverse;
}

void inverserChaineRec(char* chaine, char* chaine2, int taille) {
	
	if (!chaine[0]) {
		return;
	}
	chaine2[taille - 1] = chaine[0];
	inverserChaineRec(chaine + 1, chaine2, taille - 1);
}

char* trouverSousChaine(char* chaine, char* souschaine) {
	int t_souschaine = longueurChaine(souschaine), t_chaine = longueurChaine(chaine);
	int i = 0, a = 0, test = 0;
	
	while (chaine != NULL && i + t_souschaine <= t_chaine) {

		if (*chaine == souschaine[0] && t_souschaine > 1) {
			
			for (a = 0; a < t_souschaine; a++) {
				
				if (*(chaine + a) == souschaine[a]) {
					test++;	
					if (test == t_souschaine - 1) {
						
						return chaine;
					}
				}
				else {
					test = 0;
					break;
				}			
			}
		}
		if (*chaine == souschaine[0] && t_souschaine == 1) {
			return chaine;
		}
		i++;
		chaine++;
	}
	return NULL;
}

char* trouverSousChaineRec(char* chaine, char* souschaine, int t_chaine, int t_souschaine, int i) {
	int a = 0;

	if (*chaine == NULL || i + t_souschaine > t_chaine) {
		return NULL;
	}	
	if (*chaine == *souschaine) {
		if (t_souschaine == 1) {
			return chaine;
		}
		for (a = 0; a < t_souschaine; a++) {

			if (*(chaine + a) == souschaine[a]) {													
				continue;
			}
			else {				
				return NULL;
			}
		}
		return chaine;
	}
	return trouverSousChaineRec(chaine + 1, souschaine, t_chaine, t_souschaine, i + 1);
}

void libererChaine(char * chaine) {
	if (chaine) {
		free(chaine);
	}
}

char* trim(char* chaine, char* charactere) {

	char* occurence = trouverSousChaine(chaine, charactere);
	if (!occurence) {
		return chaine;
	}
	int compteur = 0, i = 0, a = 0, taille = longueurChaine(chaine);

	while (occurence != NULL){			
		occurence = trouverSousChaine(occurence + 1, charactere);		
		compteur++;		
	} 
	occurence = NULL;
	occurence = (char*)calloc(taille - compteur + 1, sizeof(char));	

	for(i = 0; i < taille; i++) {		
		if (chaine[i] != charactere[0]) {			
			occurence[a] = chaine[i];				
			a++;
		}					
	}
	occurence[taille - compteur] = '\0';	
	return occurence;
}

int palindrome(char* chaine) {

	if (compareChaine(chaine,inverserChaine(chaine))) {
		return 1;
	}
	else {
		return 0;
	}
}

#endif 