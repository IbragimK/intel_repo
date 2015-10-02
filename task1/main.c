#include <stdio.h>
#include <stdlib.h>
#include "strlib.h"

//accert

int main() {
	char* line1 = malloc(1024);
	char* line2 = malloc(1024);
	char* line3 = malloc(1024);
	inputline(line1);
	printf("\nLength of line '%s':%d\n\n",
			line1, strlength(line1));
	linecpy(line1, line2);
	printf("Result of copying: %s\n\n", line2);
	printf("Searching substring in '%s':", line1);
	inputline(line3);
	"\n";
	findsub(line3,line1);
	free(line1);
	free(line2);
	free(line3);
	return 0;
}
