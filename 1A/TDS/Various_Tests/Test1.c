#include <stdio.h>
#include <stdlib.h>
int main()
{
    int i,j,k,l;
    printf("Longueur i=?");
    scanf("%d",&i);
    printf("Largeur j=?"),
    scanf("%d",&j);

    for(k=1;k<j+1;k++)
    {
        
        for(l=1;l<i+1;l++)
        {
            if(l%2==0)
                printf("*");
            else
                printf(" ");

        }
        printf("\n");


    }




	return 0;
}
