#include <stdio.h>
#include <stdlib.h>

typedef struct enigma_s{
	int premier;
	char p_premier;
	int deuxieme;
	char p_deuxieme;
	int troisieme;
	char p_troisieme;
	char connexion[12];
}enigma;

enigma InitStruct(char* path);
void Init_Connexion();
int Convert(char letter);
void Rotate(int indiceR);
void GenerateInvPerm(enigma param);
int Encrypt(int letter,enigma param);
void ConnectCables(enigma param);
void Text2Value();
void InitPosition(enigma param);
