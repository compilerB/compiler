#include <stdio.h>
#include <stdlib.h>
#include "lex.h" 
FILE *fp_in, *fp_out;

int main(int argc, char *argv[]) {
	
	
	fp_in = fopen(argv[1], "rb");
	fp_out = fopen(argv[2], "wb");
	
	if(fp_in == NULL) {
		printf("Open file error.\n");
		return 0;
	}

	fclose(fp_in);
	fclose(fp_out);
	return 0;
	return 1;
}
		
