#include <stdio.h>
int main(){
    int u,n,un,t=0,min=0,max=0;           
    printf("U0=?\n");
    scanf("%d",&u);
    printf("Jusqu'a n=?\n");
    scanf("%d",&n);
    int tableau[n];
	un=u;
    for(int i=0;i<n;i++){
        while(u>1){
            if(u%2==0)            
                u/=2;    
            else            
                u=(3*u)+1;            
			t++;        
			tableau[i]=u;
            if(tableau[i]>max)
                max=tableau[i];    
            else
                min=tableau[i];
        }
		if(un%2==0)            
			un/=2;                
		else            
			un=(3*un)+1;           
    }
    printf("le temps de vol est de %d\nU%d=%d\nmin=%d\nmax=%d\n",t,n,un,min,max);  
	return 0;
}