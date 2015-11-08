#include <malloc.h>

typedef struct stack {
	int *data;
	int last;
	int data_size;
} stack_t;

stack_t* new_stack(int initial_size) {
	stack_t* stack = (stack_t*) malloc(sizeof(stack_t));
	stack->data_size = initial_size;
	if (stack->data_size <= 0) stack->data_size = 100;
	stack->last = 0;
	stack->data = (int*)malloc(sizeof(int)*stack->data_size);
	return stack;
}

void delete_stack(stack_t* stack) {
	free(stack->data);
}

void push(stack_t* stack, int val) {
	if (stack->last == stack->data_size) {
		stack->data_size = (stack->data_size * 3 + 1) / 2;
		stack->data = (int*)realloc(stack->data, stack->data_size);
	}
	stack->data[stack->last++] = val;
}

int pop(stack_t* stack) {
	int val;

	if (stack->last > 0) {
		val = stack->data[--stack->last];
		return val;
	} else {
		fprintf(stderr,
				"Attempt to retrieve an item from empty stack!\n");
		return 0;
	}
}
