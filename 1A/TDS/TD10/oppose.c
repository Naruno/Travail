#include <stdio.h>

int oppose(int n){	
	return ~n+1;
}

int main(){	
	printf("%d\n",oppose(123));
}