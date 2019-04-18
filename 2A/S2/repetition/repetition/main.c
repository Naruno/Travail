#include <stdio.h>
#include <stdlib.h>

#include "codage.h"
// Mettre en commentaire la ligne voulue pour activer le mode de compression ou decompression.

//#define compression 1
#define compression 0

//#define BLANCS 1
#define BLANCS 0

#define RLE 1
//#define RLE 0

int main() {
	if (BLANCS){
		if (compression) codageBlanc("blanc.txt");
		else codageBlanc("blanc.txtc");
	}
	if (RLE) {
		if (compression) codageRLE("rle.txt");
		else codageRLE("rle.txtc");
	}
	system("pause");
	return 0;
}