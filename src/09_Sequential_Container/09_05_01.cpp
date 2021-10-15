#include "fmt/ranges.h"
#include <vector>
#include <string>

using namespace std;
using namespace fmt;

int main()
{
	{
		const char* cp = "Hello World!";
		char noNull[] = { 'H', 'i' };
		string s1(cp);
		string s2(noNull, 2);
		string s3(noNull);	// should be an error, but at least MSVC can handle it
		string s4(cp + 6, 5);
		string s5(cp, 6, 5);
		string s6(s1, 6);
		string s7(s1, 6, 20);
		string s8(s1, 12); // if > 12, throw out of range, because s1 only has 12
	}
	{
		string s("hello world");
		string s2 = s.substr(0, 5);
		string s3 = s.substr(6);
		string s4 = s.substr(6, 11);
		string s5 = s.substr(11);	// if > 11 throw out of range
	}
	return 0;
}