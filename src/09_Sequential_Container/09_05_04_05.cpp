#include "fmt/core.h"
#include "fmt/ranges.h"
#include <vector>
#include <string>
#include <functional>

using namespace std;
using namespace fmt;

int main()
{
	{
		// compare
		string s1("123456"), s2("0123456");
		print("123456 compare 0123456 at pos 1, count 6 is {}\n", s2.compare(1, 6, s1) == 0);
	}
	{
		// numeric casting
		int i = 42;
		string s = to_string(i);
		double d = stod(s);
		print("integer to string is: {}\n", s);
	}
	{
		string s2 = "Pi is 3.1415, right?";
		double d = stod(s2.substr(s2.find_first_of("+-.0123456789")));
		print("stod can find numbers: {}\n", d);
		d = s2.find_first_of("+-.0123456789");
		print("but has to start with number: {}\n", d);
	}
	return 0;
}