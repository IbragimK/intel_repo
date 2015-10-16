#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "onegin.h"

#define MAXLEN 100

int readlines(char** lineptr, int maxlines) {
	FILE* file;
	int estr;
	int nlines = 0;

	file = fopen("onegin.txt", "r");
	assert(file);

	while (nlines < maxlines) {
		*(lineptr + nlines) = malloc(sizeof(char) * MAXLEN);
		estr = _getline(*(lineptr + nlines), MAXLEN, file);
		if (estr == 0) {
			if (feof(file) != 0) {
				break;
			} else {
				assert(feof(file));
			}
		}
		nlines++;
	}
	int i = 0;

	fclose(file);
	return nlines;
}

int _getline(char* line, int max, FILE* file) {
	if (fgets(line, max, file) == NULL)
		return 0;
	else
		return strlen(line);
}

void writelines(char** lineptr, int nlines) {
	FILE* file;
	int i = 0;

	file = fopen("onegin.out", "w");
	for (i = 0; i < nlines; i++) {
		fputs(*(lineptr + i), file);
	}
	fclose(file);
}

void binsort(char** v, int left, int right) {
	int i, last;
	void swap(char** v, int i, int j);
	
	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (strcmp(*(v + i), *(v + left)) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	binsort(v, left, last-1);
	binsort(v, last+1, right);
}

void swap(char** v, int i, int j) {
	char* temp;
	
	temp = *(v + i);
	*(v + i) = *(v + j);
	*(v + j) = temp;
}
