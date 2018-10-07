#ifndef CHAINE
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

int longueurChaine(char *p_chaine) {
	
	if (!p_chaine) {
		printf("La chaine n'est pas valide\n");
		return 0;
	}
	int i = 0;
	while (p_chaine[i] != NULL) {
		i++;
	}
	//printf("%s fait %d characteres\n", p_chaine, i);
	return i;
}

int longueurChaineRec(char *p_chaine, int p_i) {
	
	if (!p_chaine[p_i]) {
		printf("%s fait %d characteres\n", p_chaine, p_i);
		return p_i;
	}
	else {
		longueurChaineRec(p_chaine, p_i + 1);
	}
}

char* copieChaine(char* p_chaine) {
	
	int taille = longueurChaineRec(p_chaine, 0), i = 0;	
	char* copie = (char*)calloc(taille+1, sizeof(char));
	if (!copie) {
		printf("Erreur lors de l'allocation memoire de la chaine copie\n");
		return NULL;
	}
	for (i = 0; i <= taille ; i++) {
		
		copie[i] = p_chaine[i];	    
	}
	copie[taille] = '\0';
	return copie;
}

void copieChaineRec(char* p_chaine, char* p_copie) {
	p_copie[0] = p_chaine[0];
	if (!p_chaine[0]) {
		return;
	}
	else {
		copieChaineRec(p_chaine + 1, p_copie + 1);
	}
}

int compareChaine(char* p_chaine, char* p_chaine2) {

	int taille = longueurChaine(p_chaine) + 1, i = 0;
	for (i = 0; i < taille; i++) {

		if (p_chaine[0] != p_chaine2[0]) {
			return 0;
		}		
		return 1;
	}
}
int compareChaineRec(char* p_chaine, char* p_chaine2) {

	if (!p_chaine[0] && !p_chaine2[0]) {
		return 1;
	}
	if (p_chaine[0] != p_chaine2[0] || !p_chaine[0] || !p_chaine[0]) {
		return 0;
	}
	else {
		compareChaineRec(p_chaine + 1, p_chaine2 + 1);
	}
}

char* inverserChaine(char* p_chaine) {
	int taille = longueurChaine(p_chaine), i = 0;

	char* inverse = (char*) calloc(taille + 1, sizeof(char));
	if (!inverse) {
		printf("Erreur lors de l'allocation memoire de la chaine inverse\n");
		return NULL;
	}

	for (i = 0; i < taille; i++) {	
		inverse[i] = p_chaine[taille - i - 1];		
	}
	inverse[taille] = '\0';	
	return inverse;
}

void inverserChaineRec(char* p_chaine, char* p_chaine2, int p_taille) {
	
	if (!p_chaine[0]) {
		return;
	}
	p_chaine2[p_taille - 1] = p_chaine[0];
	inverserChaineRec(p_chaine + 1, p_chaine2, p_taille - 1);
}

char* trouverSousChaine(char* p_chaine, char* souschaine) {
	int t_souschaine = longueurChaine(souschaine), t_chaine = longueurChaine(p_chaine);
	int i = 0, a = 0, test = 0;
	
	while (p_chaine != NULL && i + t_souschaine <= t_chaine) {

		if (*p_chaine == souschaine[0] && t_souschaine > 1) {
			
			for (a = 0; a < t_souschaine; a++) {
				
				if (*(p_chaine + a) == souschaine[a]) {
					test++;	
					if (test == t_souschaine - 1) {
						
						return p_chaine;
					}
				}
				else {
					test = 0;
					break;
				}			
			}
		}
		if (*p_chaine == souschaine[0] && t_souschaine == 1) {
			return p_chaine;
		}
		i++;
		p_chaine++;
	}
	return NULL;
}

char* trouverSousChaineRec(char* p_chaine, char* p_souschaine, int p_t_chaine, int p_t_souschaine, int p_i) {
	int a = 0;

	if (*p_chaine == NULL || p_i + p_t_souschaine > p_t_chaine) {
		return NULL;
	}	
	if (*p_chaine == *p_souschaine) {
		if (p_t_souschaine == 1) {
			return p_chaine;
		}
		for (a = 0; a < p_t_souschaine; a++) {

			if (*(p_chaine + a) == p_souschaine[a]) {
				continue;
			}
			else {				
				return NULL;
			}
		}
		return p_chaine;
	}
	return trouverSousChaineRec(p_chaine + 1, p_souschaine, p_t_chaine, p_t_souschaine, p_i + 1);
}

void libererChaine(char * p_chaine) {
	if (p_chaine) {
		free(p_chaine);
	}
}

char* trim(char* p_chaine, char* p_charactere) {
	// Enlève des charactères d'une chaine.
	char* occurence = trouverSousChaine(p_chaine, p_charactere);
	if (!occurence) {
		return p_chaine;
	}
	int compteur = 0, i = 0, a = 0, taille = longueurChaine(p_chaine);

	while (occurence != NULL){			
		occurence = trouverSousChaine(occurence + 1, p_charactere);
		compteur++;		
	} 
	occurence = NULL;
	occurence = (char*)calloc(taille - compteur + 1, sizeof(char));	

	for(i = 0; i < taille; i++) {		
		if (p_chaine[i] != p_charactere[0]) {
			occurence[a] = p_chaine[i];				
			a++;
		}					
	}
	occurence[taille - compteur] = '\0';	
	return occurence;
}

int palindrome(char* p_chaine) {

	if (compareChaine(p_chaine,inverserChaine(p_chaine))) {
		return 1;
	}
	else {
		return 0;
	}
}

int findFirstOf(char* p_chaine, char* p_chaine2) {

	int t_chaine = longueurChaine(p_chaine), t_chaine2 = longueurChaine(p_chaine2), i = 0, j = 0;

	for (i = 0; i < t_chaine; i++) {

		for (j = 0; j < t_chaine2; j++) {

			if (p_chaine[i] == p_chaine2[j]) {
				return i;
			}
		}
	}
	return -1;
}

int findLastOf(char* p_chaine, char* p_chaine2) {

	int t_chaine = longueurChaine(p_chaine) - 1, t_chaine2 = longueurChaine(p_chaine2) - 1 , i = 0, j = 0;

	for (i = t_chaine; i > -1 ; i--) {

		for (j = t_chaine2; j > -1 ; j--) {

			if (p_chaine[i] == p_chaine2[j]) {
				return i;
			}
		}
	}
	return -1;
}

int findFirstNotOf(char* p_chaine, char* p_chaine2) {

	int t_chaine = longueurChaine(p_chaine), t_chaine2 = longueurChaine(p_chaine2), i = 0, j = 0, egal = 0;

	for (i = 0; i < t_chaine; i++) {
		egal = 0;
		for (j = 0; j < t_chaine2; j++) {

			if (p_chaine[i] == p_chaine2[j]) {
				egal++;
			}
		}
		if (!egal) {
			return i;
		}
	}
	return -1;
}
int findLastNotOf(char* p_chaine, char* p_chaine2) {

	int t_chaine = longueurChaine(p_chaine) - 1, t_chaine2 = longueurChaine(p_chaine2) - 1, i = 0, j = 0, egal = 0;

	for (i = t_chaine; i > -1; i--) {
		egal = 0;
		for (j = t_chaine2; j > -1; j--) {

			if (p_chaine[i] == p_chaine2[j]) {
				egal++;
			}
		}
		if (!egal) {
			return i;
		}
	}
	return -1;

}

int estDans(char p_char, char* p_souschaine) {

	int t_souschaine = longueurChaine(p_souschaine), i = 0;
	for (i = 0; i < t_souschaine; i++) {
		if (p_char == p_souschaine[i]) {
			return 1;
		}
	}
	return 0;
}

char** split(char* p_chaine, char* p_souschaine, int* taille) {
	
	int t_chaine = longueurChaine(p_chaine), t_chaine2 = longueurChaine(p_souschaine), i = 0, j = 0, ligne = 0, colonne = 0, occurences = 0;

	for (i = 0; i < t_chaine; i++) {
		for (j = 0; j < t_chaine2; j++) {
			if (p_chaine[i] == p_souschaine[j]) {
				occurences++;
				break;
			}
		}
	}	
	*taille = occurences;
	char** res = (char**)calloc(occurences, sizeof(char*));
	for (i = 0; i < occurences; i++) {
		res[i] = (char*)calloc(t_chaine + 1, sizeof(char));
	}	

	for (i = 0; i < t_chaine; i++) {
		
		if (estDans(p_chaine[i], p_souschaine)) {
			res[ligne][colonne] = '\0';
			colonne = 0;
			ligne++;
		}
		else {
			res[ligne][colonne] = p_chaine[i];
			colonne++;
		}		
	}
	return res;
}

char* toUpper(char* p_chaine) {

	int taille = longueurChaine(p_chaine), i = 0;
	char* min = (char*)calloc(taille + 1, sizeof(char));
	
	for (i = 0; i < taille; i++) {		
		if (p_chaine[i] > 96 && p_chaine[i] < 123) {
			min[i] = p_chaine[i] - 32;
		}
		else {
			min[i] = p_chaine[i];
		}		
	}
	min[taille] = '\0';
	return min;
}

char* toLower(char* p_chaine) {
	int taille = longueurChaine(p_chaine), i = 0;
	char* min = (char*)calloc(taille + 1, sizeof(char));

	for (i = 0; i < taille; i++) {
		if (p_chaine[i] > 64 && p_chaine[i] < 91) {
			min[i] = p_chaine[i] + 32;
		}
		else {
			min[i] = p_chaine[i];
		}
	}
	min[taille] = '\0';
	return min;
}

char* inverseCase(char* p_chaine) {

	int taille = longueurChaine(p_chaine), i = 0;
	char* inverse = (char*)calloc(taille + 1, sizeof(char));

	for (i = 0; i < taille; i++) {
		if (p_chaine[i] > 64 && p_chaine[i] < 91) {
			inverse[i] = p_chaine[i] + 32;
			continue;
		}
		if (p_chaine[i] > 96 && p_chaine[i] < 123) {
			inverse[i] = p_chaine[i] - 32;
			continue;
		}		
		inverse[i] = p_chaine[i];		
	}
	inverse[taille] = '\0';
	return inverse;
}
#endif 