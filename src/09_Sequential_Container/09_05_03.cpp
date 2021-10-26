#include "fmt/ranges.h"
#include <vector>
#include <string>
#include <functional>

using namespace std;
using namespace fmt;

int main()
{
	{
		// .find, case sensitive
		string name("AnnaBelle");
		auto pos1 = name.find("Anna");
		print("found Anna in AnnaBelle?: {}\n", pos1 == 0);
		auto pos2 = name.find("anna");
		print("didn't found anna in AnnaBelle?: {}\n", pos2 == string::npos);
	}
	{
		// find any matched of a string
		string numbers("012345679"), name("l4d"), name2("aabbcc");
		auto pos = name.find_first_of(numbers);
		auto pos2 = name2.find_first_of(numbers);
		print("the first of {}\n", pos);
		print("the first of {}\n", pos2);
	}
	{
		// specify where to search
		string numbers("012345679"), name("l4d 2th edition 3");
		string::size_type pos = 0;
		while((pos = name.find_first_of(numbers, pos))!=string::npos)
		{
			print("found number at index: {} element is {}\n", pos, name[pos]);
			++pos;
		}
	}
	{
		// reverse search
		string river("Mississippi");
		auto first_pos = river.find("is");
		auto last_pos = river.rfind("is");
		print("first position is {}, last position is {}\n", first_pos, last_pos);
	}
	return 0;
}