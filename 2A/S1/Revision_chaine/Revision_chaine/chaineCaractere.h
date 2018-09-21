int longueurChaine(char *chaine);
int longueurChaineRec(char *chaine, int i);

char* copieChaine(char* chaine);
char* copieChaineRec(char* chaine, char* chaine2);

int compareChaine(char* chaine, char* chaine2);
int compareChaineRec(char* chaine, char* chaine2);

char* inverserChaine(char* chaine);
void inverserChaineRec(char* chaine, char* chaine2, int taille);

char* trouverSousChaine(char* chaine, char* souschaine);
char* trouverSousChaineRec(char* chaine, char* souschaine, int t_chaine, int t_souschaine, int i);

void libererChaine(char * chaine);

char* trim(char* chaine, char* charactere);
int palindrome(char* chaine);