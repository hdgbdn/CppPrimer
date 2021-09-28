#include "fmt/ranges.h"
#include <list>
#include <vector>

using namespace std;
using namespace fmt;

int main()
{
	{
		// 9.25
		list<int> ilist{ 1,2,3,4,5 };
		ilist.erase(ilist.begin(), ilist.begin());	// nothing deleted
		print("after erase begin begin, ilist is {}\n", ilist);
		ilist.erase(ilist.end(), ilist.end());	// nothing deleted
		print("after erase end end, ilist is {}\n", ilist);
		ilist.erase(ilist.begin(), ilist.end());	// clear
		print("after erase begin end, ilist is {}\n", ilist);
	}
	{
		// 9.26
		int ia[] = { 0,1,2,3,4,5,6,7,8,9 };
		vector<int> ivec(ia, end(ia));
		list<int> ilst(ia, end(ia));

		auto it = ivec.begin();
		while (it != ivec.end())
		{
			if (*it % 2)
			{
				it = ivec.erase(it);
				print("after erase an odd element, ivec is: {}\n", ivec);
			}
			else ++it;
		}
		auto it2 = ilst.begin();
		while (it2 != ilst.end())
		{
			if (!(*it2 % 2))
			{
				it2 = ilst.erase(it2);
				print("after erase an even element, ilst is: {}\n", ilst);
			}
			else ++it2;
		}
	}
}