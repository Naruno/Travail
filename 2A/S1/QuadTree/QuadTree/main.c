#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "BMP.h"
#include "QuadTree.h"

int main() {
	int compression, height;
	// Please change the names if needed.

	char* pictureToRead = "image.BMP";
	char* pictureToWrite = "image1.BMP";
	char* nameQuad = "picture.quad";
	char* nameQuadToWrite = "picture.BMP";
	byte threshold = 0;
	picture* pct = ReadPicture(pictureToRead);
	PrintHeader(pct->datas);
	if (!WritePicture(pct, pictureToWrite)) {
		printf("Couldn't Write the picture\n");
			return -1;
	}	
	QuadTree * Quad = CreateQuad(pct->matrix, 0, 0, pct->datas->height, threshold);
	SaveQuad(nameQuad, Quad);
	FreeQuad(&Quad);	
	FreeBMP(pct);
	Quad = LoadQuad(nameQuad);
	height = HeightQuad(Quad);
	printf("Choose the level of compression (integer) : ");
	scanf("%d", &compression);
	compression = floor(compression);
	if (compression < 0) {
		compression = 0;
	}
	if (compression > height) {
		compression = height;
	}	
	CreatePicture(nameQuadToWrite, Quad, (byte)(height - compression));
	FreeQuad(&Quad);
	system("pause");
	return 0;
}

