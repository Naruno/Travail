#include "liste.h"
#include <Windows.h>

int main()
{
	Liste *maListe = initialisation();
	Element* nouveau = (Element*)calloc(1, sizeof(*nouveau));
	Element* test = (Element*)calloc(1, sizeof(*test));
	Element* ok = (Element*)calloc(1, sizeof(*ok));	
	
	nouveau->m_nombre = 10;
	insertionFRec(maListe->m_premier, nouveau);
	afficherListe(maListe);

	test->m_nombre = 9;
	insertionFRec(maListe->m_premier, test);
	afficherListe(maListe);

	ok->m_nombre = 8;
	insertionFRec(maListe->m_premier, ok);
	afficherListe(maListe);
	
	suppressionFRec(maListe->m_premier);
	afficherListe(maListe);

	suppressionFRec(maListe->m_premier);
	afficherListe(maListe);

	suppressionFRec(maListe->m_premier);
	afficherListe(maListe);
	
	//ajoutTriCroissanto(&(maListe->m_premier), nouveau);
	
	
	system("pause");
	
	free(maListe);
	return 0;
}