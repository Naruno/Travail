#include <stdio.h>
#include <math.h>
int main()
{
    float x,h=0.001f,e;
    e=1.0f;

    for(x=0.0f;x<=1.0f;x+=h){
        e+=e*h;
    }
    printf("e=%f\n",e);
    //printf("e=%f\n",expf(1.0f));
	printf( "%f", 73.0);
    return 0;
}
