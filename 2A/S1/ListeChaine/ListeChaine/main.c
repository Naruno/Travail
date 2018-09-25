#include "liste.h"
#include <Windows.h>

int main()
{
	Element* maListe = createListNode(2);

	printList(maListe);

	maListe = addLast(maListe, 10);
	printList(maListe);
	addSortAsco(&maListe, 7);
	printList(maListe);
	maListe = suppressionF(maListe);
	
	printList(maListe);
	system("pause");
	
	freeList(maListe);
	return 0;
}