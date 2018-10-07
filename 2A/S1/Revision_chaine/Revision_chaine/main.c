#define _CRT_SECURE_NO_WARNINGS
#include "chaineCaractere.h"
#include <stdio.h>
#include <Windows.h>

int main() {
	char *chaine = "4 5 + 3 10 5 / - x", *s_chaine = "+-x/";
	char **tab = NULL;
	int i = 0, a = 0;
	printf("%s\n", chaine);
	tab = split(chaine, s_chaine, &a);
	
	for (i = 0; i < a; i++) {
		printf("[%s]", tab[i]);
	}
	printf("\n");

	system("pause");	
	
	return 0;
}