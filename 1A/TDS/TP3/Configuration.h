#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

typedef struct Config_s{ 
		int hauteur;
		int largeur;
		int motif;
		int naissance[8];
		int survie[8];
		char image;
		float vitesse;
		int nstop;
	}Config;
	
Config InitStruct(char* path);
int AlloGame(Config info);
int DrawGame(Config info, int gene);
int IsInRange(int ligne,int colonne,Config info);
int NbCasesAdj(int ligne,int colonne,Config info);
void UpdateGame(Config info);
void PlayGame(Config info);
