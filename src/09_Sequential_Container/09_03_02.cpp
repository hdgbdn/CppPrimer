#include <vector>
#include <string>
#include <list>
#include <forward_list>
#include <deque>
#include "fmt/core.h"
#include "fmt/ranges.h"
#include <fmt/color.h>

using namespace std;

int main()
{
	{
		// forward_list don't have back() function
		vector<int> iVec{ 1,2,3,4 };
		if (!iVec.empty())
		{
			auto val = *iVec.begin(), val2 = iVec.front();
			auto last = iVec.end();
			auto val3 = *(--last);		// end() is pointed to the element behind the last element
			auto val4 = iVec.back();
		}
	}
	{
		// front back [] at, returns the reference of element
		// but must use reference
		vector<int> iVec{ 1,2,3,4 };
		if(!iVec.empty())
		{
			auto val = iVec.front();
			val = 99;
			auto & val2 = iVec.back();
			val2 = 99;
			fmt::print("{}\n", iVec);
		}
	}
	{
		vector<int> iVec{ 1,2,3,4 };
		fmt::print("illegal to access out of range operator [] {}", iVec[3]);
		try
		{
			fmt::print("but can use at {} \n", iVec.at(4));
		}
		catch (const exception& e)
		{
			fmt::print("An exception has been thrown: {} \n" , e.what());
		}
	}
}