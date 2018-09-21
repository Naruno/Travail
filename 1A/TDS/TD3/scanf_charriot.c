#include <stdio.h>

void clean_stdin(void)
{
    int c;
    do
    {
        c=getchar();
    }while (c != '\n' && c!= EOF);
}

int main()
{
    int i, res=0;
    while(res<10)
    {
        i=scanf("%d",&res);
        if (i<=0)
            clean_stdin();
        printf("i: %d\t-- %d --\n",i,res);
    }
    return 0;
}
