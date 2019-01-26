#include <stdio.h>
#include <stdlib.h>

#include "test.h"

int main() {

	{
		int tab[3] = { 1, tab[0] + 1, tab[1] + 1 };
		int* tab_test = test(tab);
		printf("[%d]\n", tab_test[1]);
	}
	system("pause");
	return 0;
}
