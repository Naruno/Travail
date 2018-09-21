#include <stdio.h>
int main()
{       
    for(int i=0,int j=1;i<30;i+=2,j+=1){
        printf("i=%d, j=%d\n",i,j);		
        if(i==j)
            i=2*j;
        else
            printf("%d\n",j);
	}		
    printf("\nAu revoir\n");
    return 0;
}
