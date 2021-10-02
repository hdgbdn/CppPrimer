#include "fmt/ranges.h"
#include <vector>

using namespace std;
using namespace fmt;

int main()
{
	// 9.29
	vector<int> ivec(25, 42);
	ivec.resize(100);
	print("after resize, the ivec is: {}\n", ivec);	// the new allocated memory initialized by 0

	// 9.30
	// the single parameter version of resize require a default constructor for element;
}