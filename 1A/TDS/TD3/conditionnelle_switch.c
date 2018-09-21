#include <stdio.h>
int main()
{
    int a=42;
    switch(a)
    {
        case 0:
            printf("Ca vaut 0\n");
        break;
        case 1:
            printf("Ca vaut 1\n");
        break;
        case 2:
            printf("Ca vaut 2\n");
        break;
        case 3:
            printf("Ca vaut 3\n");
        break;
        case 4:
            printf("Ca vaut 4\n");
        break;
        case 5:
            printf("Ca vaut 5\n");
        break;
        default:
            printf("Ca vaut un truc\n");
    }
    return 0;
}