#define _CRT_SECURE_NO_WARNINGS
#include "chaineCaractere.h"
#include <stdio.h>
#include <Windows.h>

int main() {
	char* chaine = "laval", chaine2 = "aeiouy";
	
	printf("%d\n", findFirstOf(chaine, chaine2));
	system("pause");	
	
	return 0;
}