#ifndef BMP_H
#define BMP_H
#pragma once
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long dword;

#pragma pack(push, 1)
typedef struct pixel_s {
	byte value[3];
}pixel;
#pragma pack(pop)

// BMP header
#pragma pack(push, 1)
typedef struct BMPINFOHEADER {
	// Type of file, BM for BMP.
	char type[2];
	// Lenght of file, in bytes.
	dword size; 
	// Unused.
	dword reserved;  
	// Shift of data from the begenning of the file (in bytes).
	dword offset;  
	// Length of the header : 40 bytes for BMP.
	dword headersize; 
	// Picture's width.
	dword width; 
	// Picture's height.
	dword height;  
	// Number of planes, 1 for BMP.
	word planes;  
	// Depth of colors (bit per pixel) : 24 for BMP.
	word bitsperpixel; 				
	// Compression : 0 dans notre cas, pas de compression.
	dword compression; 
	// Size of picture : 0 or size of picture in bytes (size-54).
	dword sizeimage;  
	// Resolution of printing according to width.
	dword xpixelspermeter; 
	// Resolution of printing according to height.
	dword ypixelspermeter; 
	// number of colors in the palet : 0 in our case.
	dword colorused; 						
	// 0.
	dword colorsimportant; 

}bmpInfoHeader;
#pragma pack(pop)
enum couleur {
	RED, 
	GREEN, 
	BLUE,
	NB_COLOR
};
#pragma pack(push, 1)
typedef struct picture_s {
	bmpInfoHeader* datas;
	pixel** matrix;
}picture;
#pragma pack(pop)
// Read a picture and return a picture with header informations and a matrix of pixel.
picture *ReadPicture(char *p_pctPath);
// Print the header datas of a bmpInfoHeader variable.
void PrintHeader(bmpInfoHeader *p_datas);
// Write p_pct to p_pctpath.
int WritePicture(picture *p_pct, char *p_pctPath);
// Free a picture variable.
void FreeBMP(picture* p_pct);
#endif