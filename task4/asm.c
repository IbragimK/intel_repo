#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMDS 100

typedef struct cmds {
	int* list;
	int size;
} cmds_t;

long int file_size(FILE *f);
long int read_cmds_norm(char* b, FILE* f);
cmds_t translate_cmds_norm(char* b, long int b_s);
char* _get_next_val(char* b, long int c_p, long int b_s);
int ncmd(int* c_r);

int main() {
	FILE* f_cmds_norm = fopen("prog.myasm", "rb");
	char* buf = calloc(MAX_CMDS, sizeof(char));
	long int buf_size;
	cmds_t cmds_rev;

	cmds_rev.list = calloc(MAX_CMDS, sizeof(int));
	buf_size = read_cmds_norm(buf, f_cmds_norm);
	cmds_rev = translate_cmds_norm(buf, buf_size);

	fclose(f_cmds_norm);

	FILE* f_cmds_rev = fopen("commands.myexe", "wb");
	
	fwrite(cmds_rev.list, sizeof(int), cmds_rev.size, f_cmds_rev);
	
	fclose(f_cmds_rev);

	return 0;
}

cmds_t translate_cmds_norm(char* buf, long int buf_size) {
	cmds_t cmd_rev;
	char* next_val = malloc(sizeof(char) * 10);
	long int curr_pos = 0;
	long int count_cmds = 0;
	
	cmd_rev.list = calloc(MAX_CMDS, sizeof(int));
	while ((curr_pos < buf_size) &&
				(next_val = _get_next_val(buf, curr_pos, buf_size))) {
		#define DEF_CMD(name, num, code)		\
		if (!strcmp(next_val, #name))			\
			*(cmd_rev.list + count_cmds) = num;	\
		else
		#include "cmd_list.h"
			*(cmd_rev.list + count_cmds) = atoi(next_val);
		curr_pos += strlen(next_val) + 1;
		count_cmds++;
	}
	#undef DEF_CMD
	cmd_rev.size = count_cmds;

	return cmd_rev;
}

char* _get_next_val(char* buf, long int curr_pos, long int buf_size) {
	char* curr_val = calloc(10, sizeof(char));
	long int count = 0;

	while (!isspace(*(buf + curr_pos))) {
		*(curr_val + count) = *(buf + curr_pos);
		curr_pos++;
		count++;
	}
	if (curr_val == "END") {
		return 0;
	}

	return curr_val;
}

long int read_cmds_norm(char* buf, FILE* file) {
	long int fsize = file_size(file);
	
	fread(buf, sizeof(char), fsize, file);

	return fsize;
}

long int file_size(FILE *file) {
	long int save_pos, size_of_file;

	save_pos = ftell(file);
	fseek(file, 0L, SEEK_END);
	size_of_file = ftell(file);
	fseek(file, save_pos, SEEK_SET);

	return(size_of_file);
}



