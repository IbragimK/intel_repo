#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define CALC_LEN(vector)	\
	vector.length_ = sqrt(vector.x_*vector.x_ + vector.y_*vector.y_ + vector.z_*vector.z_)

class CVector {
	private:
		double x_, y_, z_; // coordinates of vector
		double length_;
	public:
		CVector();
		~CVector();

		int read(double xval, double yval, double zval);
		int print();

		friend CVector& operator+=(CVector& left, const CVector& right);
		friend CVector& operator-=(CVector& left, const CVector& right);
		friend const CVector operator+(const CVector& left, const CVector& right); // binary '+'
		friend const CVector operator-(const CVector& left, const CVector& right); // binary '-'
		friend const CVector operator*(const double lambda, const CVector& vector); // left multiplication
		friend const CVector operator*(const CVector& vector, const double lambda); // right multiplication
		friend const double operator^(const CVector& left, const CVector& right); // scalar multiplicaton
		friend const CVector operator*(const CVector& left, const CVector& right); // vector multiplication
};

// constructor
CVector::CVector():
	x_(),
	y_(),
	z_(),
	length_()
{}

// destructor
CVector::~CVector()
{}

int CVector::read(double xval, double yval, double zval) {
	x_ = xval;
	y_ = yval;
	z_ = zval;
	length_ = sqrt(x_*x_ + y_*y_ + z_*z_);

	return 0;
}

int CVector::print() {
	printf("(%.2f, %.2f, %.2f)\nlength = %.2f\n", x_, y_, z_, length_);
	
	return 0;
}

CVector& operator+=(CVector& left, const CVector& right) {
	left.x_ += right.x_;
	left.y_ += right.y_;
	left.z_ += right.z_;
	CALC_LEN(left);

	return left;
}

CVector& operator-=(CVector& left, const CVector& right) {
	left.x_ -= right.x_;
	left.y_ -= right.y_;
	left.z_ -= right.z_;
	CALC_LEN(left);

	return left;
}

const CVector operator+(const CVector& left, const CVector& right) {
	CVector temp;
	temp.x_ = left.x_ + right.x_;
	temp.y_ = left.y_ + right.y_;
	temp.z_ = left.z_ + right.z_;
	CALC_LEN(temp);

	return temp;
}

const CVector operator-(const CVector& left, const CVector& right) {
	CVector temp;
	temp.x_ = left.x_ - right.x_;
	temp.y_ = left.y_ - right.y_;
	temp.z_ = left.z_ - right.z_;
	CALC_LEN(temp);

	return temp;
}

const CVector operator*(const double lambda, const CVector& vector) {
	CVector temp;
	temp.x_ = vector.x_ * lambda;
	temp.y_ = vector.y_ * lambda;
	temp.z_ = vector.z_ * lambda;
	CALC_LEN(temp);

	return temp;
}

const CVector operator*(const CVector& vector, const double lambda) {
	CVector temp;
	temp.x_ = vector.x_ * lambda;
	temp.y_ = vector.y_ * lambda;
	temp.z_ = vector.z_ * lambda;
	CALC_LEN(temp);

	return temp;
}

const double operator^(const CVector& left, const CVector& right) {
	return left.x_*right.x_ + left.y_*right.y_ + left.z_*right.z_;
}

const CVector operator*(const CVector& left, const CVector& right) {
	CVector temp;
	temp.x_ = left.y_ * right.z_ - right.y_ * left.z_;
	temp.y_ = left.z_ * right.x_ - right.z_ * left.x_;
	temp.z_ = left.x_ * right.y_ - right.x_ * left.y_;
	CALC_LEN(temp);

	return temp;
}

int main() {
	CVector v1, v2, v3;

	v1.read(1, 2, 3);
	v2.read(4, 5, 6);

	//v1 += v2;
	v3 = v1*v2;
	v3.print();

/*	double scal;
	scal = v1^v2;

	printf("(v1, v2) = %.2f\n", scal);
*/
	return 0;
}
