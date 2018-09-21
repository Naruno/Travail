#include <stdio.h>
typedef struct str1{
		int a;
		int b;
		char c;
	}str1_s;
	
int main()
{
	str1_s var;
	
	var.a=10;
	var.b=5;
	var.c='c';
	
	printf("a=%d\nb=%d\nc=%c\n",var.a,var.b,var.c);
	
	var.a=var.b;
	var.b=(int)var.c;
	printf("a=%d\nb=%d\nc=%c\n",var.a,var.b,var.c);
	return 0;
}
