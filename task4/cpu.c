#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stack.h"

#define MAX_CMDS 100

typedef struct CmdInfo {
	int num;
	char* name;
} CmdInfo_t;

#define DEF_CMD(name, num, code) cmd_##name = num,
enum commands {
	#include "cmd_list.h"
	cmd_END = 0,
};
#undef DEF_CMD

const CmdInfo_t cmd[] = {
	#define DEF_CMD(name, num, code)	\
	{cmd_##name, #name},
	#include "cmd_list.h"
	#undef DEF_CMD
	{cmd_END, "END"},
};

int compile(int* buf);
long int file_size(FILE* f);
long int calc(int* buf, int n_e);

int main() {
	int num_elmts;
	int* buf = calloc(MAX_CMDS, sizeof(char));
	
	num_elmts = compile(buf);

	printf("%ld\n", calc(buf, num_elmts));

	return 0;
}

int compile(int* buf) {
	FILE* file = fopen("commands.myexe", "rb");
	int buf_size = file_size(file);
	int num_elmts;

	num_elmts = fread(buf, sizeof(int), buf_size, file);

	fclose(file);

	return num_elmts;
}

long int calc(int* buf, int num_elmts) {
	long int res = 0;
	int i = 0;
	int val = 0;
	stack_t stk = *new_stack(num_elmts);

	while (buf[i]) {
		switch (buf[i]) {
			#define DEF_CMD(name, num, code)	\
			case num: code;						\
					  break;
			#include "cmd_list.h"
			#undef DEF_CMD
			default: {fprintf(stderr, "ERROR: unknown command\n");
					 	exit(1);
					 };
		}
		i++;
	}
	res = *(stk.data);

	delete_stack(&stk);

	return res;
}

long int file_size(FILE* file) {
	long int save_pos, size_of_file;

	save_pos = ftell(file);
	fseek(file, 0L, SEEK_END);
	size_of_file = ftell(file);
	fseek(file, save_pos, SEEK_SET);

	return(size_of_file);
}





