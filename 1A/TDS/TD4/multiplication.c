#include <stdio.h>
int addition(int a,int b)
{    
    return a+=b;
}
int multiplication(int a,int b)
{
    return a*=b;
}
int main()
{
    int a,b,c;
    do{
    printf("Que valent a,b,c ? a et b >=0\n");
    scanf("%d",&a);
    scanf("%d",&b);
    }while(a<0||b<0);
    scanf("%d",&c);
    int i,pow=a,res=1;
    printf("%d*%d=%d\n%d*(%d+%d)=%d\n%d*%d*%d=%d\n",a,b,multiplication(a,b),a,b,c,multiplication(a,addition(b,c)),a,b,c,multiplication(a,multiplication(b,c)));
    for(i=1;i<b;i++)
    {
        pow=multiplication(pow,a);
    }
    if(b==0)
        pow=1;
    printf("%d^%d=%d\n",a,b,pow);
    for(i=1;i<=a;i++)
    {
        if(a==0)
            res=1;
        res=multiplication(res,a-(a-i));
    }
    printf("%d!=%d\n",a,res);
    return 0;
}
