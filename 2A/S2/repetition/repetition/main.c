#include <stdio.h>
#include <stdlib.h>

#include "codage.h"
// Mettre en commentaire la ligne voulue pour activer le mode de compression ou decompression.

#define compression 1
//#define compression 0

int main() {
	if(compression) codageBlanc("blanc.txt");
	else codageBlanc("blanc.txtc");		
	system("pause");
	return 0;
}