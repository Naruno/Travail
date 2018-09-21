#include <stdio.h>

int Miror(int N)
{
    int a,b=0;
    do{
        a=N%10;
        N/=10;
        b=b*10+a;
       }while(N>0);
    return b;
}

int NbDigit(int N)
{
    int c=0;
    do{
        N/=10;
        c++;
    }while(N>0);
    return c;
}

int power(int a, int b)
{
    int pow=1;
    for(int i=1;i<=b;i++)
    {
        pow*=a;
    }
    return pow;
}
int Palindromize(int N)
{
    return (N/10)*power(10,NbDigit(N))+Miror(N);
}

int main()
{
    int N=123;
    printf("Avant : N=%d\nApres : N=%d\n%d a %d chiffres\nPalindrome : %d\n",N,Miror(N),N,NbDigit(N),Palindromize(N));
    return 0;
}
