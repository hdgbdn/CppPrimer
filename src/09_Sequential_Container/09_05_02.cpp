#include "fmt/ranges.h"
#include <vector>
#include <string>

using namespace std;
using namespace fmt;

int main()
{
	{
		// string has operator =, assign, insert, erase
		string a = "abcdefg";
		a.assign(19, 'a');
		print("after a.assign(19, 'a'): {} \n", a);
		a.insert(a.begin() + 1, 'b');
		print("after a.insert(a.begin() + 1, 'b'): {} \n", a);
		a.erase(a.begin(), a.begin() + 1);
		print("after a.erase(a.begin(), a.begin() + 1): {} \n", a);
	}
	{
		// but string has additional insert and erase
		string s = "abcdefg";
		s.insert(s.size(), 10, 'z');
		print("after s.insert(s.size(), 10, 'z'): {} \n", s);
		s.erase(s.size() - 10, 9);
		print("after s.erase(s.size() - 10, 9): {} \n", s);

		// and our old friend: c-style char array
		const char* cp = "Stately, plump Buck";
		s.assign(cp, 4);
		print("after s.assign(cp, 4): {} \n", s);
		s.insert(s.size(), cp + 4);
		print("s.insert(s.size(), cp + 4): {} \n", s);		// insert right in the position:s.size(), if the value is 0, then will insert in the beginning
	}
	{
		string s = "some thing", s2 = "some other thing";
		s.insert(0, s2);
		print("after s.insert(0, s2): {} \n", s);
		s.insert(0, s2, 0, s2.size());
		print("after s.insert(0, s2, 0, s2.size()): {} \n", s);
	}
	{
		// append and replace
		// unique string functions
		string s("C++ Primer"), s2 = s;
		s.insert(s.size(), " 4th Ed.");
		s2.append(" 4th Ed.");
		print("after s.insert(s.size(), \" 4th Ed.\"): {} \n", s);
		s.erase(11, 3);
		s.insert(11, "5th");
		s2.replace(s2.begin() + 11, s2.begin() + 14, "Fifth123");
		// the replace don't require the the input string length equal the given length
		// we give 3 count, but add 7 
		print("after s2.replace(s2.begin() + 11, s2.begin() + 14, \"Fifth123\"): {} \n", s2);		
	}
}