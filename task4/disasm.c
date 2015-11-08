/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
*/
#define MAX_CMDS 100

int read_cmds_rev(int* buf);
long int file_size(FILE *file);
void itoa(int n, char* s); 
void reverse(char* s);
int translate_cmds_rev(int* buf, char** buf_rev, int num_elmts);

int main () {
	int* buf = calloc(MAX_CMDS, sizeof(int));
	char** buf_rev = calloc(MAX_CMDS, sizeof(char));
	int num_elmts;

	num_elmts = read_cmds_rev(buf);
	translate_cmds_rev(buf, buf_rev, num_elmts);
//	write_cmds_norm(buf);

	return 0;
}

int read_cmds_rev(int* buf) {
	FILE* file = fopen("commands.myexe", "rb");
	long int fsize = file_size(file);
	int num_elmts = 0;

	num_elmts = fread(buf, sizeof(int), fsize, file);
	
	fclose(file);

	return num_elmts;
}

int translate_cmds_rev(int* buf, char** buf_rev, int num_elmts) {
	int i = 0;
	char flag = 1;

	while (i < num_elmts) {
		*(buf_rev + i) = (char*) calloc(10, sizeof(char));
		if (flag) {
			switch (buf[i]) {
				#define DEF_CMD(name, num, code)				\
				case num: strcpy(#name, (*(buf_rev + i)));		\
						  break;	
				#include "cmd_list.h"
				#undef DEF_CMD
				default: {/*fprintf(stderr, "ERROR: unknown command\n");
							exit(1);*/
						break;
						 };
			}
		} else {
			itoa(buf[i], *(buf_rev + i));
			flag = 1;
		}
		if (buf[i] == 1) flag = 0;
		i++;
	}

	return 0;	
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






