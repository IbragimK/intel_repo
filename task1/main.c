#include <stdio.h>
#include <stdlib.h>
#include "strlib.h"

#define ASSERT(cond) if (!cond) {				\
			printf("Error: invalid pointer\n");	\
			exit (-1);							\
		}
 
int main() {				
	char* linexmpl = malloc(5*sizeof(char));
	char* cpdline = malloc(5*sizeof(char));
	char* subline = malloc(5*sizeof(char));
	int pos = 0;
	inputline(linexmpl);
	ASSERT(linexmpl > 0);
	printf("\nLength of line '%s':%d\n\n",
			linexmpl, strlength(linexmpl));
	linecpy(linexmpl, cpdline);
	printf("Result of copying:%s\n\n", cpdline);
	printf("Searching substring in '%s':", linexmpl);
	inputline(subline);
	ASSERT(subline > 0);
	"\n";
	if (pos = findsub(subline, linexmpl))
		printf("\nSubstring is found on position:%d\n", pos);
	else
		printf("\nSubstring is no found\n");
	free(linexmpl);
	free(cpdline);
	free(subline);
	return 0;
}
