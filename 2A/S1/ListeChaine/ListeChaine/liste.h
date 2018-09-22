typedef struct Element Element;
struct Element{

	int m_nombre;
	Element* m_suivant;
};

typedef struct Liste Liste;
struct Liste {

	Element *m_premier;
};

Liste* initialisation();
void dInsertion(Liste* p_liste, int p_nombre);
void dSuppression(Liste* p_liste);

void insertionF(Liste* p_liste, int p_nombre);
void suppressionF(Liste* p_liste);

Element* insertionFRec(Element* p_element, Element* p_nouveau);
Element* suppressionFRec(Element* p_element);

void afficherListe(Liste* p_liste);

Element* ajoutTriCroissant(Element* p_element, Element* p_nouveau);
void ajoutTriCroissanto(Element** p_element, Element* p_nouveau);
