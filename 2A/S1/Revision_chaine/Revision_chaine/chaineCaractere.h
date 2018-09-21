int longueurChaine(char *p_chaine);
int longueurChaineRec(char *p_chaine, int p_i);

char* copieChaine(char* p_chaine);
char* copieChaineRec(char* p_chaine, char* p_chaine2);

int compareChaine(char* p_chaine, char* p_chaine2);
int compareChaineRec(char* p_chaine, char* p_chaine2);

char* inverserChaine(char* p_chaine);
void inverserChaineRec(char* p_chaine, char* p_chaine2, int p_taille);

char* trouverSousChaine(char* p_chaine, char* p_souschaine);
char* trouverSousChaineRec(char* p_chaine, char* p_souschaine, int p_t_chaine, int p_t_souschaine, int p_i);

void libererChaine(char* p_chaine);

char* trim(char* p_chaine, char* p_charactere);
int palindrome(char* p_chaine);

int findFirstOf(char* p_chaine, char* p_chaine2);