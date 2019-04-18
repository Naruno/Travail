#include "graphes.h"
#include "vld.h"
int main() {

	Sommet* graphe = creerSommet('A');

	ajouterSommet(&(graphe->m_liste_arc), 'B');
	ajouterSommet(&(graphe->m_liste_arc), 'D');
	ajouterSommet(&(graphe->m_liste_arc), 'F');

	ajouterSommet(&(graphe->m_liste_arc->m_sommet->m_liste_arc), 'C');
	ajouterSommet(&(graphe->m_liste_arc->m_sommet->m_liste_arc), 'E');
	largeur(graphe);

	//profondeur(graphe);
	
	//largeur(graphe);
	printf("\n");

	libererGraphe(graphe);	
	system("pause");
	return 0;
}