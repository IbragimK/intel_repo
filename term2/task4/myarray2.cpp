#include <stdio.h>
#include <assert.h>

// array with checking borders 

template <typename data_T = int>
class CVector {
	private:
		static const int size_ = 4096;
		data_T data_[size_];
	public:
		CVector();
		~CVector();

		// brackets with checking
		data_T& operator[](int index) {
			assert(0 <= index && index < size_);
			
			return data_[index];
		};
};

// constructor
template <typename data_T>
CVector <data_T>::CVector():
	data_()
{}

// destructor
template <typename data_T>
CVector <data_T>::~CVector()
{}

	
int main() {
	CVector <double> v;

	v[2] = 13;
	v[4095] = 93;
	printf("%f\n", v[2]);
	printf("%f\n", v[4095]);

	return 0;
}
