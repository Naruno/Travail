#include <stdio.h>

int main(){		
	 
   int A[] = {12, 23, 34, 45, 56, 67, 78, 89, 90};
   int *p;
   p = A;
   
   printf("a) %d\n",*p+2);
   printf("b) %d\n",*(p+2));
   printf("c) %d\n",&p+1);
   printf("d) %d\n",&A[4]-3);
   printf("e) %d\n",A+3);
   printf("f) %ld\n",&A[7]-p);
   printf("g) %d\n",p+(*p-10));
   printf("h) %d\n",*(p+*(p+8)-A[7]));  
   return 0;
} 
 
 
 
 
