#include <stdio.h>
#include <stdlib.h>
#include "strlib.h"

int inputline(char* line) {
	while ((*line++ = getchar()) != '\n');
	*--line = '\0';
	return 0;
}

int strlength(char* line) {
	char* pline = line;
	while (*pline != '\0')
		pline++;
	return pline - line;
}

void linecpy(char* fromline, char* toline) {
	while ((*toline++ = *fromline++) != '\0');
}

int linecmp(char* fline, char* sline) {
	for ( ; *fline == *sline; fline++, sline++)
		if (*fline == '\0')
			return 0;
	return *fline - *sline;
}

int findsub(char* substr, char* eldstr) {
	char* peldstr = malloc(5*sizeof(char));
	char* tempstr = malloc(5*sizeof(char));
	peldstr = eldstr;
	int lensub = strlength(substr);
	int leneld = strlength(eldstr);
	while (peldstr - eldstr + lensub <= leneld) {
		linecpy(peldstr++, tempstr);
		if (!linecmp(substr, _linecut(tempstr, lensub))) {
			return peldstr - eldstr;
		}
	}
	return 0;
}

char* _linecut(char* line, int lencuts) { 
	while (*(line++ + lencuts) = *((char*)""));
	return --line; 
}
