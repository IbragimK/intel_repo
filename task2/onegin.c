#include <stdio.h>
#include <stdlib.h>
#include "onegin.h"

#define MAXLINES 5000

int main () {
	int nlines;
	char** lineptr = malloc(sizeof(char) * MAXLINES);

	if (nlines = readlines(lineptr, MAXLINES)) {
		binsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("Error: input too big to sort\n");
		return 1;
	}

}
