#include <Windows.h>
#include <stdio.h>

char * Accent(const char * mess) {
	static char retour[1024];
	CharToOem(mess, retour); // API Windows.
	return retour;
}

void print(const char* text) {
	printf("%s", Accent(text));
}