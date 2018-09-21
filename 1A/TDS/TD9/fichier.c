#include <stdio.h>
#include <stdlib.h>

void SizeFile(char* path){	
	FILE *pfile=NULL;	
	pfile=fopen(path,"r");
	
	if (pfile!=NULL){		
		fseek(pfile,0,SEEK_END);
		printf("%ld\n",ftell(pfile));
	}
	fclose(pfile);
}

void Warning(char* path){
	FILE *pfile=NULL;	
	pfile=fopen(path,"r");
	char continue_f;
	
	if (pfile!=NULL){		
		printf("Ce fichier existe, il sera écrasé.\nContinuer ? (y/n) : ");
		scanf("%c",&continue_f);
		
		switch(continue_f){
			
			case 'y':
				fclose(pfile);
				pfile=fopen(path,"w");
				break;
			
			case 'n':
				exit(0);
		}
	}		
}

int main(){	
	//SizeFile("text.txt");
	Warning("text.txt");	
	return 0;
}