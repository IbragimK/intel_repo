#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100

int sort_mtx(int*, int, int);
int get_mtx(int*, int, int, FILE*);
int put_mtx(int*, int, int);
void _swap(int*, int*);

int main() {
	FILE* file;
	int* mtx;
	int m, n;

	file = fopen("test.txt", "r");
	m = fgetc(file);
	n = fgetc(file);
	mtx = malloc(sizeof(int) * m*n);

	get_mtx(mtx, m, n, file);
	sort_mtx(mtx, m, n);
	put_mtx(mtx, m, n);

	fclose(file);
	return 0;
}


int get_mtx(int* mtx, int m, int n, FILE* file) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			*(mtx + i*n +j) = fgetc(file);
			printf("%d ", *(mtx + i*n +j));
		}
		printf("\n");
	}
	return 0;
}

int put_mtx(int* mtx, int m, int n) {
	FILE* file = fopen("test.out", "w");
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			fputc(*(mtx + i*n + j), file);			
		}
		fputc('\n', file);
	}
	fclose(file);
	return 0;
}

int sort_mtx(int* mtx, int m, int n) {
	int i, j;
	for (i = 0; i < m*n - 1; i++) {
		for (j = 0; j < m*n - i - 1; j++) {
			if (*(mtx + j) < *(mtx + j + 1))
				_swap((mtx + j), (mtx + j + 1));
		}
	}
	return 0;
}

void _swap(int* a, int* b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

