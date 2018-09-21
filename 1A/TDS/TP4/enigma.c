#include "enigma.h"

int connexions[26],rotor[3][26],Reflector[26],invRotor[3][26],shift[3];
char textRotor[3][26]={{'E','K','M','F','L','G','D','Q','V','Z','N','T','O','W','Y','H','X','U','S','P','A','I','B','R','C','J'},
					   {'A','J','D','K','S','I','R','U','X','B','L','H','W','T','M','C','Q','G','Z','N','P','Y','F','V','O','E'},
					   {'B','D','F','H','J','L','C','P','R','T','X','V','Z','N','Y','E','I','W','G','A','K','M','U','S','Q','O'}};					   
char textReflector[26]={'E','J','M','Z','A','L','Y','X','V','B','W','F','C','R','Q','U','O','N','T','S','P','I','K','H','G','D'};				   

enigma InitStruct(char* path){
	enigma param;
	FILE *fichier = fopen(path,"r");
	if(fichier != NULL){		
		fscanf(fichier,
		"01 %d%c %d%c %d%c %c%c %c%c %c%c",
		&param.premier,&param.p_premier,&param.deuxieme,&param.p_deuxieme,&param.troisieme,&param.p_troisieme,
		&param.connexion[0],&param.connexion[1],&param.connexion[2],&param.connexion[3],
		&param.connexion[4],&param.connexion[5]);		
		fclose(fichier);		
	}
	return param;
}	
//%c%c %c%c %c%c //,&param.connexion[6],&param.connexion[7],&param.connexion[8],&param.connexion[9],&param.connexion[10],&param.connexion[11]
int Convert(char letter){ //Conversion de char vers alphabet [0;25]
	if (letter>64 && letter<91)
		return letter-65;		
	if (letter>96 && letter<123)
		return letter-97;		
	else 
		return EXIT_FAILURE;
}

void Text2Value(){ //Conversion des rotors alphabetiques en numeriques	
	for (int i=0;i<3;i++){
		for (int j=0;j<26;j++)
			rotor[i][j]=Convert(textRotor[i][j]);		
	}	
	for (int i=0;i<26;i++)
		Reflector[i]=Convert(textReflector[i]);
}

void GenerateInvPerm(enigma param){	//Creation des rotors inverses	
		for (int j=0;j<26;j++)
			invRotor[param.premier-1][rotor[param.premier-1][j]]=j;	
		for (int j=0;j<26;j++)
			invRotor[param.deuxieme-1][rotor[param.deuxieme-1][j]]=j;
		for (int j=0;j<26;j++)
			invRotor[param.troisieme-1][rotor[param.troisieme-1][j]]=j;		
}

void Init_Connexion(){ //Initialise le tableau de connexions
	for (int i=0;i<26;i++)	
		connexions[i]=i;		
}

void ConnectCables(enigma param){ //Regle les permutations de lettres	
	for (int i=0;i<6;i+=2){	//A changer selon le nombre de paires de lettres			
			connexions[Convert(param.connexion[i])]=Convert(param.connexion[i+1]);			
			connexions[Convert(param.connexion[i+1])]=Convert(param.connexion[i]);
	}								
}

void InitPosition(enigma param){ //Initialise les decallages initiaux des 3 rotors //On ramene les rotors entrés (1 2 3) en (0 1 2) par -1
	for (int i=0,compteur=0;i<25;i++,compteur++){
		if (rotor[param.premier-1][i]==Convert(param.p_premier)){
			shift[param.premier-1]=compteur;
			break;
		}		
	}
	for (int i=0,compteur=0;i<25;i++,compteur++){
		if (rotor[param.deuxieme-1][i]==Convert(param.p_deuxieme)){
			shift[param.deuxieme-1]=compteur;
			break;
		}		
	}
	for (int i=0,compteur=0;i<25;i++,compteur++){
		if (rotor[param.troisieme-1][i]==Convert(param.p_troisieme)){
			shift[param.troisieme-1]=compteur;
			break;
		}		
	}
}

int Encrypt(int letter,enigma param){	
	letter=connexions[letter];	
	letter=(rotor[param.premier-1][(letter+26-shift[param.premier-1])%26]+shift[param.premier-1])%26;
	letter=(rotor[param.deuxieme-1][(letter+26-shift[param.deuxieme-1])%26]+shift[param.deuxieme-1])%26;
	letter=(rotor[param.troisieme-1][(letter+26-shift[param.troisieme-1])%26]+shift[param.troisieme-1])%26;
	letter=Reflector[letter];
	letter=(invRotor[param.troisieme-1][(letter+26-shift[param.troisieme-1])%26]+shift[ param.troisieme-1])%26;	
	letter=(invRotor[param.deuxieme-1][(letter+26-shift[param.deuxieme-1])%26]+shift[ param.deuxieme-1])%26;
	letter=(invRotor[param.premier-1][(letter+26-shift[param.premier-1])%26]+shift[ param.premier-1])%26;
	letter=connexions[letter];
	
	shift[param.premier-1]++; //Decallage obligatoire du premier rotor	
	if (shift[param.premier-1]==26){
		shift[param.premier-1]=0;
		shift[param.deuxieme-1]++;
				
		if (shift[param.deuxieme-1]==26){
			shift[param.deuxieme-1]=0;
			shift[param.troisieme-1]++;
						
			if (shift[param.troisieme-1]==26)
				shift[param.troisieme-1]=0;
		}
	}	
	return letter;
}

int main(int argc, char **argv){ 	
	enigma param=InitStruct("enigma.txt");	
	Text2Value();
	GenerateInvPerm(param);	
	Init_Connexion();	
	ConnectCables(param);
	InitPosition(param);    
    for(int i=1;i<argc;i++){     
        for (int j=0;argv[i][j]!='\0';j++) 
			printf("%c",Encrypt(Convert(argv[i][j]),param)+97); //Chiffrement lettre par lettre	                    
        printf("\n");		
	}
	return 0;
}