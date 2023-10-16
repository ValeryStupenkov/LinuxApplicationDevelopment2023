#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char *p;
	int m, n= 0;
	int s = 1;
	int i;
	
	if (argc == 1) {
		printf("help\n");
		return 0;
	}
	else if (argc == 2) {
		n = strtol(argv[1], &p, 10);
	}
	else if (argc == 3) {
		m = strtol(argv[1], &p, 10);
		n = strtol(argv[2], &p, 10);
	}
	else {
		m = strtol(argv[1], &p, 10);
		n = strtol(argv[2], &p, 10);
		s = strtol(argv[3], &p, 10);
	}
	
	for (i=m; i<n; i=i+s){
		printf("%d\n", i);
	}
	
	return 0;
}
