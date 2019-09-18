#include "Vec3.h"
#include <stdio.h>

int main() {

	vec3 vec1 = set3(1, 2, 1);
	vec3 vec2 = set3(1, 2, 1);
	
	afficheVec3(add3(vec1, vec2));
	afficheVec3(sub3(vec1, vec2));

	afficheVec3(copy3(vec1));

	printf("%f\n", dot3(vec1, vec2));
	return 0;
}