#include <stdio.h>
#include <assert.h>

// array with checking borders 
class CVector {
	private:
		static const int size_ = 4096;
		int data_[size_];
	public:
		CVector();
		~CVector();

		// brackets with checking
		int& operator[](int index) {
			assert(0 <= index && index < size_);
			
			return data_[index];
		};
};

// constructor
CVector::CVector():
	data_()
{}

// destructor
CVector::~CVector()
{}

	
int main() {
	CVector v;

	v[2] = 13;
	v[4095] = 93;

	printf("%d\n", v[2]);
	printf("%d\n", v[4095]);

	return 0;
}
