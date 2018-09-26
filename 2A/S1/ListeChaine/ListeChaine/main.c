#include "liste.h"
#include <Windows.h>

int main()
{
	Element* maListe = createListNode(2);
	Element* res;
	int a = 0;
	printList(maListe);

	maListe = addLast(maListe, 10);
	printList(maListe);
	addSortAsco(&maListe, 7);
	maListe = addLast(maListe, 99);
	printList(maListe);
	a = listLength(maListe);
	res = at(maListe, a);

	printf("taille liste = %d\n", a);
	printList(res);
	printList(maListe);
	maListe = pop(maListe, &a);
	printList(maListe);
	system("pause");
	
	freeList(maListe);
	return 0;
}