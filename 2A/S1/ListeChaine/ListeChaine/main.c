#pragma once
#include <Windows.h>
#include "liste.h"
#include "piles.h"
#include "application.h"

int main()
{
	node* test = createListNode("Bonjour");
	addLast(test, "je");
	addLast(test, "me");
	addLast(test, "nomme");
	addLast(test, "055");
	printList_str(test);
	system("pause");
	return 0;
}