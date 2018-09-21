#define _CRT_SECURE_NO_WARNINGS
#include "chaineCaractere.h"
#include <stdio.h>
#include <Windows.h>

int main() {
	char *chaine = "C'etait bien_le WEI !?! ", *min = NULL;
	printf("%s\n", chaine);
	min = inverseCase(chaine);
	printf("%s\n", min);

	system("pause");	
	
	return 0;
}