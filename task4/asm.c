#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMDS 100

long int file_size(FILE *f);
long int read_buf_verb(char* b_v);
int translate_buf_verb(int* b_n, char* b_v, long int b_s);
char* _get_next_val(char* b_v, long int c_p, long int b_s);
void write_buf_numeric(int* b_n, int n_e);
long int size_of_buffer(void);

int main() {
	char* buf_verb = calloc(MAX_CMDS, sizeof(char));
	int num_elmts;
	long int buf_size;
	int* buf_numeric = calloc(MAX_CMDS, sizeof(int));

	buf_numeric = calloc(MAX_CMDS, sizeof(int));
	buf_size = read_buf_verb(buf_verb);
	num_elmts = translate_buf_verb(buf_numeric, buf_verb, buf_size);
	write_buf_numeric(buf_numeric, num_elmts);

	return 0;
}

int translate_buf_verb(int* buf_numeric, char* buf_verb, long int buf_size) {
	char* next_val = malloc(sizeof(char) * 10);
	long int curr_pos = 0;
	long int num_elmts = 0;
	
	while ((curr_pos < buf_size) &&
				(next_val = _get_next_val(buf_verb, curr_pos, buf_size))) {
		#define DEF_CMD(name, num, code)		\
		if (!strcmp(next_val, #name))			\
			*(buf_numeric + num_elmts) = num;	\
		else
		#include "cmd_list.h"
		#undef DEF_CMD
		*(buf_numeric + num_elmts) = atoi(next_val);
		curr_pos += strlen(next_val) + 1;
		num_elmts++;
	}

	return num_elmts;
}

char* _get_next_val(char* buf_verb, long int curr_pos, long int buf_size) {
	char* curr_val = calloc(10, sizeof(char));
	long int count = 0;

	while (!isspace(*(buf_verb + curr_pos))) {
		*(curr_val + count) = *(buf_verb + curr_pos);
		curr_pos++;
		count++;
	}
	if (curr_val == "END") {
		return 0;
	}

	return curr_val;
}

long int read_buf_verb(char* buf_verb) {
	FILE* file = fopen("prog.myasm", "rb");
	long int fsize = file_size(file);
	long int buf_size;
	
	buf_size = fread(buf_verb, sizeof(char), fsize, file);

	fclose(file);

	return buf_size;
}

void write_buf_numeric(int* buf_numeric, int num_elmts) {
	FILE* file = fopen("commands.myexe", "wb");
	
	fwrite(buf_numeric, sizeof(int), num_elmts, file);
	
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

