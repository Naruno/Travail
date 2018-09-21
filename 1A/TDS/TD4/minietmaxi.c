#include <stdio.h>
int maximum(int a,int b)
{
   if (a<b)
      return b;
   else
      return a;
}
int minimum3(int a,int b,int c)
{
    if(a<b)
    {
        if (a<c)
            return a;
        else
            return c;
    }
     else
     {
        if (b<c)
            return b;
        else
            return c;
     }
}
int main()
{
    int val1=-5,val2=15,val3=8;
    printf("Le plus petit de %d,%d,%d est %d\n",val1,val2,val3,minimum3(val1,val2,val3));
    if(maximum(val1,maximum(val2,val3))==val1)
    {
            printf("%d\n",val1);
            if(maximum(val2,val3)==val2)            
                printf("%d\n%d\n",val2,val3);
            else
                printf("%d\n%d\n",val3,val2);
            return 0;
    }
    else
        if(maximum(val1,maximum(val2,val3))==val2)
        {
            printf("%d\n",val2);
            if(maximum(val1,val3)==val1)
                printf("%d\n%d\n",val1,val3);
            else
                printf("%d\n%d\n",val3,val1);
            return 0;
        }
        if(maximum(val1,maximum(val2,val3))==val3)
        {
            printf("%d\n",val3);
            if(maximum(val1,val2)==val1)            
                printf("%d\n%d\n",val1,val2);
            else
                printf("%d\n%d\n",val2,val3);
            return 0;
        }
    return 0;
}