#include "Huffman.h"
#include "fileBin.h"
#include "vld.h"

int main(int argc, char** argv) {

	if(argc > 1)
		compression(argv[1]);

	system("pause");
	return 0;
}