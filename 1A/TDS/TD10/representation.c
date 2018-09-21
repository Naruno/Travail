#include <stdio.h>

int main(){	
	int i=8,j=5;
	float x=0.005;
	char c='c',d='d';	
	printf("%d\n",(3*i-2*j)%(2*d-c));
	printf("%d\n",2*((i/5)+(4*(j-3))%(i+j-2)));
	printf("%d\n%d\n%d\n",i<=j,j!=6,c==99);
	printf("%d\n",5*(i+j)>'c');
	printf("%d\n",(i>0)&&(i<5));
	printf("%d\n",((i>0)||(j<5))&&(x>0));
	printf("%d\n%d\n",i&j,i|j);	
	
	printf("\n\n%d\n%d\n",(((4<<2)+(12>>1))&7),5^7);
	return 0;
}