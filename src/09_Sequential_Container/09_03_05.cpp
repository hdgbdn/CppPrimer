#include "fmt/ranges.h"
#include <list>
#include <string>
#include <functional>

using namespace std;
using namespace fmt;

int main()
{
	{
		// resize
		list<int> ilist(10, 42);
		print("the original list: {}\n", ilist);
		ilist.resize(15);
		print("resize to 15: {}\n", ilist);
		ilist.resize(25, -1);
		print("resize to 25 with -1: {}\n", ilist);
		ilist.resize(5, -2);
		print("resize to 5 with -1: {}\n", ilist);
	}
	return 0;
}