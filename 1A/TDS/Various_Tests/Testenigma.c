#include <stdio.h>

int main(){
	var aImage = ["image1", "image2", "image3"],
	searchValue = "image3", // valeur à trouver (d.gEBI.src)
	idValue = aImage.indexOf(searchValue);
	printf("%d\n",idValue);
	return 0;
}