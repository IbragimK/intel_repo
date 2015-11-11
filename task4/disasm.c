#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_CMDS 100

int read_buf_numeric(int* buf_numeric);
long int file_size(FILE *file);
void itoa(int n, char* s); 
void reverse(char* s);
void translate_buf_numeric(int* buf_numeric, char** buf_verb, int num_elmts);
void write_buf_verb(char** buf_verb, int num_elmts);

int main() {
	int* buf_numeric = calloc(MAX_CMDS, sizeof(int));
	char** buf_verb = calloc(MAX_CMDS, sizeof(char*));
	int num_elmts;


	num_elmts = read_buf_numeric(buf_numeric);

	int i;

	for (i = 0; i < num_elmts; i++) {
		*(buf_verb + i) = (char*) calloc(10, sizeof(char));
	}
	translate_buf_numeric(buf_numeric, buf_verb, num_elmts);
	write_buf_verb(buf_verb, num_elmts);

	return 0;
}

int read_buf_numeric(int* buf_numeric) {
	FILE* file = fopen("commands.myexe", "rb");
	long int fsize = file_size(file);
	int num_elmts;

	num_elmts = fread(buf_numeric, sizeof(int), fsize, file);
	
	fclose(file);

	return num_elmts;
}

void translate_buf_numeric(int* buf_numeric, char** buf_verb, int num_elmts) {
	int i = 0;
	char flag = 1;

	while (i < num_elmts) {
		if (flag) {
			switch (buf_numeric[i]) {
				#define DEF_CMD(name, num, code)				\
				case num: strcpy(buf_verb[i], #name);			\
						  break;
				#include "cmd_list.h"
				#undef DEF_CMD
				case 0: strcpy(buf_verb[i], "END");
						break;
				default: {fprintf(stderr, "ERROR: unknown command\n");
							exit(1);
						 };
			}
		} else {
			itoa(buf_numeric[i], buf_verb[i]);
			flag = 1;
		}
		if (buf_numeric[i] == 1) flag = 0;
		i++;
	}	
}

void write_buf_verb(char** buf_verb, int num_elmts) {
	FILE* file = fopen("check.myasm", "w");

	fwrite(buf_verb, sizeof(char*), num_elmts, file);

	fclose(file);
}

long int file_size(FILE *file) {
	long int save_pos, size_of_file;

	save_pos = ftell(file);
	fseek(file, 0L, SEEK_END);
	size_of_file = ftell(file);
	fseek(file, save_pos, SEEK_SET);

	return(size_of_file);
}

void itoa(int n, char* s) {
	int i, sign;
		
	if ((sign = n) < 0)
	n = -n;
    i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);  
	if (sign < 0) s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

void reverse(char* s) {
	int i, j;
	char c;	    

	for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}






