#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
int get(void)//fonction qui detecte la saisie d une touche
{
  struct termios oldt,newt;
  int ch,oldf;  
  tcgetattr(STDIN_FILENO,&oldt);
  newt=oldt;
  newt.c_lflag &=~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO,TCSANOW,&newt);
  oldf=fcntl(STDIN_FILENO,F_GETFL,0);
  fcntl(STDIN_FILENO,F_SETFL,oldf | O_NONBLOCK);
  ch=getchar();
  tcsetattr(STDIN_FILENO,TCSANOW,&oldt);
  fcntl(STDIN_FILENO,F_SETFL,oldf);
  if(ch!=EOF)
  {
    ungetc(ch,stdin);
    return 1;
  }
  return 0;
}
void CompteARebours(int duree)//boucle qui tourne pendant duree secondes
{   
	clock_t start_t = clock();
	while((clock()-start_t)/CLOCKS_PER_SEC < duree);     
}
double TempsAleatoire (int max)//boucle qui tourne pendant sec_alea secondes
{	
    int sec_alea=(int)(rand()%(max)+1);    
	CompteARebours(sec_alea);    
    return 0;
}
double DeroulerJeu (int duree)//Affiche le compte a rebours
{	
	for(int i=3;i>0;i--){		
        printf("%d...\n\n",i);
		CompteARebours(duree/3);		       
    }   
	TempsAleatoire(5);	
	clock_t start_t = clock(),end_t,test=clock();
    do{		
		if(((double)(clock()-test)/(double)CLOCKS_PER_SEC)>(float)duree/20)
		{
			printf("°");  
			test=clock();			
		}
    }while(get()!=1 && (clock()-start_t)/CLOCKS_PER_SEC<duree);
    end_t=clock();
	if(((end_t-start_t)/CLOCKS_PER_SEC)!=0){
		printf("\nReaction de %f s\n",(double)(end_t-start_t)/CLOCKS_PER_SEC);
		if((double)(end_t-start_t)/CLOCKS_PER_SEC>=duree)
			printf("Vous êtes vraiment lent !\n");	
		else if((double)(end_t-start_t)/CLOCKS_PER_SEC<0.5)
				printf("Tres Rapide !\n");		
		else if((double)(end_t-start_t)/CLOCKS_PER_SEC<1)
				printf("Plutot rapide\n");
	}else printf("On a dit reaction... pas prediction\n");			
    return 0;
}
int main()
{	 
	 system("clear");	 
	 srand(time(NULL));     
     DeroulerJeu(3);  
     return 0;
}
