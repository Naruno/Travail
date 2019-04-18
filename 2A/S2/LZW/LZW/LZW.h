#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void LZW(FILE* p_phrase);

typedef struct code {
	char* m_octets;
	int m_size;
}code;

typedef struct dico {
	code* m_dico;
	char m_size;
	int m_index;
}dico;