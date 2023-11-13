#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Error: wrong number of parameters\n");
		exit(1);
	}
	
	char *srcname = argv[1];
	char *dstname = argv[2];
	FILE *fsrc, *fdst;
	char c;
	int status;
	
	fsrc = fopen(srcname, "r");
	if (fsrc == NULL) {
		printf("Error: can't open source file %s\n", srcname);
		exit(2); 
	}
	
	fdst = fopen(dstname, "w");
	if (fdst == NULL) {
		printf("Error: can't open destination file %s\n", dstname);
		exit(3);
	}
	
	c = fgetc(fsrc);
	if (ferror(fsrc)) {
		printf("Error while reading from source file");
		exit(4);
	}
	while (c != EOF) {
		fputc(c, fdst);
		if (ferror(fdst)) {
			printf("Error while writing to destination file");
			exit(5);
		}
		c = fgetc(fsrc);
		if (ferror(fsrc)) {
			printf("Error while reading from source file");
			exit(4);
		}
	}
	
	status = fclose(fsrc);
	if (status == -1) {
		printf("Error while closing source file");
		exit(6);
	}
	status = fclose(fdst);
	if (status == -1) {
		printf("Error while closing destination file");
		exit(7);
	}
	
	if (remove(srcname) == -1) {
		printf("Error while removing source file");
		exit(8);
	}
	
	return 0;
}
