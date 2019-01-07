#include "Reversi.h"

void afficheOthellier(char p_othellier[8][8]) {
	printf("  ");
	for (char lettre = 'A'; lettre <= 'H'; lettre++) {
		printf(" %c ", lettre);
	}
	printf("\n");
	for (int i = 0; i < 8; i++) {
		printf("%d ", i + 1);
		for (int j = 0; j < 8; j++) {
			printf("[%d]", p_othellier[i][j]);
		}
		printf("\n");
	}
}