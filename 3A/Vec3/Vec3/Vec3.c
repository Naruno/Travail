#include "Vec3.h"

#define _VEC3_C_

LIB_API vec3 set3(float p_x, float p_y, float p_z) {

	vec3 res;
	res.x = p_x;
	res.y = p_y;
	res.z = p_z;
	return res;
}

LIB_API void afficheVec3(vec3 p_vec) {

	printf("[%.2f,%.2f,%.2f]\n", p_vec.x, p_vec.y, p_vec.z);
}

LIB_API vec3 add3(vec3 p_vect1, vec3 p_vect2) {

	return set3(p_vect1.x + p_vect2.x, p_vect1.y + p_vect2.y, p_vect1.z + p_vect2.z);
}

LIB_API vec3 sub3(vec3 p_vect1, vec3 p_vect2) {
	
	return set3(p_vect1.x - p_vect2.x, p_vect1.y - p_vect2.y, p_vect1.z - p_vect2.z);
}

LIB_API float distance3(vec3 p_vect1, vec3 p_vect2) {

	return (float) sqrt(pow((p_vect2.x - p_vect1.x), 2) + pow((p_vect2.y - p_vect1.y), 2) + pow((p_vect2.z - p_vect1.z), 2));
}

LIB_API float dot3(vec3 p_vect1, vec3 p_vect2) {

	return p_vect1.x * p_vect2.x + p_vect1.y * p_vect2.y + p_vect1.z * p_vect2.z;
}

LIB_API vec3 copy3(vec3 p_vect) {

	return set3(p_vect.x, p_vect.y, p_vect.z);
}

LIB_API vec3 mul3(vec3 p_vec, float p_nombre){

	return set3(p_vec.x * p_nombre, p_vec.y * p_nombre, p_vec.z * p_nombre);
}

LIB_API vec3 div3(vec3 p_vec, float p_nombre){
	if (p_nombre == 0){			
		printf("Division par zero impossible\n");
		return set3(0, 0, 0);
	}	
	return set3(p_vec.x / p_nombre, p_vec.y / p_nombre, p_vec.z / p_nombre);
}

LIB_API float norm3(vec3 p_vec){

	return sqrt(p_vec.x * p_vec.x + p_vec.y * p_vec.y + p_vec.z * p_vec.z);
}

LIB_API vec3 normalize3(vec3 p_vec){

	return div3(p_vec, norm3(p_vec));
}


LIB_API vec3 cross3(vec3 p_vect1, vec3 p_vect2){
	vec3 result;

	result.x = (p_vect1.y * p_vect2.z) - (p_vect1.z * p_vect2.y);
	result.y = (p_vect1.z * p_vect2.x) - (p_vect1.x * p_vect2.z);
	result.z = (p_vect1.x * p_vect2.y) - (p_vect1.y * p_vect2.x);

	return result;
}

LIB_API vec3 reflect3(vec3 p_vect1, vec3 p_vect2){

	return add3(mul3(mul3(normalize3(p_vect2), dot3(p_vect1, normalize3(p_vect2))), 2), p_vect1);
}