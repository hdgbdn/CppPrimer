#include "fmt/ranges.h"
#include <vector>
#include <string>

using namespace std;
using namespace fmt;

int main()
{
	// 9.35
	// capacity is the size of allocated memory, size is the size of memory used;

	// 9.36 capacity may equal to size, but will never smaller than size

	// 9.37 because list don't use continuous memory, and array has a fixed memory

	// 9.38
	vector<int> ivec;
	for (int i = 0; i < 20; ++i)
	{
		ivec.push_back(1);
		print("{} : capacity is:{} \n", ivec, ivec.capacity());
		print("{} : size is:{} \n", ivec, ivec.size());
	}

	// 9.39
	// first, reversed 1024 cell for a string vector, then copy every input string into the vector,
	// then resize will add anther size/2 of default constructed string

	// 9.40
	vector<string> svec256;
	for (int i = 0; i < 256; ++i)
		svec256.push_back(" ");
	print("string vector 256, capacity is {}\n", svec256.capacity());

	vector<string> svec512;
	for (int i = 0; i < 512; ++i)
		svec512.push_back(" ");
	print("string vector 512, capacity is {}\n", svec512.capacity());


	vector<string> svec1000;
	for (int i = 0; i < 1000; ++i)
		svec1000.push_back(" ");
	print("string vector 1000, capacity is {}\n", svec1000.capacity());

	vector<string> svec1024;
	for (int i = 0; i < 1024; ++i)
		svec1024.push_back(" ");
	print("string vector 1024, capacity is {}\n", svec1024.capacity());

	return 0;
}