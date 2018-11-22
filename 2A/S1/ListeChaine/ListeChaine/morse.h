typedef struct noeud_morse_s noeud_morse;
struct noeud_morse_s{

	
	char lettre;
	noeud_morse *m_gauche;
	noeud_morse *m_droit;

};

typedef struct pile_morse_s pile_morse;
struct pile_morse_s {

	char* morse;
	char lettre;
	pile_morse *m_next;
};

noeud_morse * creerNoeud_Morse(char lettre);
void libererMorse(noeud_morse ** p_ppRoot);
int hauteur_m(noeud_morse * p_pRoot);
void afficher_Morse(noeud_morse * p_pRoot, int profondeur);
void affichage_propre_m(char* message, noeud_morse * p_pRoot);
pile_morse* pop_stack_m(pile_morse** p_head);
pile_morse* addLast_m(pile_morse* p_pRoot, char* chaine, char lettre);
void printPile_m(pile_morse* p_pRoot);
void ajout_m(noeud_morse ** p_pRoot, char* morse, char lettre);
pile_morse* pop_m(pile_morse* p_pRoot, pile_morse * save);
pile_morse * charger_liste();
noeud_morse * chargerMorse_Vide(noeud_morse * noeud, int profondeur);
void test_Morse();