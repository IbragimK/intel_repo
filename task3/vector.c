#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*Structure description*/
struct Vector_t {
	double x, y;
};

typedef struct Vector_t Vector_t;

void Vector_ctor(Vector_t* This, double x, double y);
void Vector_dtor(Vector_t* This);
char Vector_OK(const Vector_t* This);
void Vector_dump(Vector_t* This);
Vector_t Vector_operator_plus(const Vector_t* vect1, const Vector_t* vect2);



int main() {
	Vector_t *vect1 = malloc(sizeof(Vector_t));
	Vector_t *vect2 = malloc(sizeof(Vector_t));
	Vector_t *res = malloc(sizeof(Vector_t));
	Vector_ctor(vect1, 1, 3);
	Vector_ctor(vect2, 55, 61);
	*res = Vector_operator_plus(vect1, vect2);
	printf("(%.f,%.f)\n", res -> x, res -> y);
	return 0;
}

/*Constructor of stucture*/
void Vector_ctor(Vector_t* This, double x, double y) {
	assert(This);
	This -> x = x;		// This -> x ~ (*This).x
	This -> y = y;

}

/*Destructor of structure*/
void Vector_dtor(Vector_t* This) {
	This -> x = -1;
	This -> y = -1;

}

/*Check on the errors in structures*/
char Vector_OK(const Vector_t* This) {
	return
		This != NULL;


}

/*Dump of structure*/
void Vector_dump(Vector_t* This) {
	printf("x = %.f\ny = %.f\n", This -> x, This -> y);
}

/*The sum of vectors*/
Vector_t Vector_operator_plus(const Vector_t* vect1, const Vector_t* vect2) {
	assert(Vector_OK(vect1));
	assert(Vector_OK(vect2));
	
	Vector_t res = {};
	Vector_ctor(&res, vect1 -> x, vect1 -> y);
	res.x += vect2 -> x;
	res.y += vect2 -> y;

	assert(Vector_OK(vect1));
	assert(Vector_OK(vect1));
	assert(Vector_OK(&res));

	return res;
} 
