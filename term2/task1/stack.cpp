#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// class of stack stored array and size
class CStack {
	private:
		int data_[128];
		int size_;
	public:
// some functions to work with the stack
		CStack();
		~CStack();
		int push(int val);
		int pop();
		int print();
};

// constructor
CStack::CStack():
	data_(),
	size_(0)
{}

// destructor
CStack::~CStack() {
	int i = 0;

	for (i = 0; i < size_; i++) {
		data_[i] = data_[size_-i-1] - 1;
	}
	size_ = -1;
}

// push function 
int CStack::push(int val) {
	assert(&val);

	data_[size_++] = val;

	return 0;
}

// pop function
int CStack::pop() {
	return data_[--size_];
}

// function prints size and data of stack (not dump)
int CStack::print() {
	int i = 0;
	
	assert(size_ >= 0);
	printf("Size: %d\n", size_);
	for (i = 0; i < size_; i++) {
		printf("%d ", data_[i]);
	}
	printf("\n");
}

// nothing interesting
int main() {
	CStack stack;

	stack.push(13);
	stack.push(17);
	stack.print();

	int taken_val;
	
	taken_val = stack.pop();
	printf("Taken value: %d\n", taken_val);
	stack.print();
	
	return 0;
}
