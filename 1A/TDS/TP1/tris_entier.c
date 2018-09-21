#include <stdio.h>
int i,n=0,p=9999,g=0;
int main()
{
    printf("Entrez 10 entiers:\n");
    for (i=0;i<9;i+=1)
    {
        scanf("%d\n",&n);
        if (n<=p)
            p=n;
        if (n>=g)
            g=n;
    }
    printf("Le plus petit nombre entre est %d, le plus grand est %d\n",p,g);
    return 0;
}
