#include "fmt/ranges.h"
#include <list>
#include <vector>

using namespace std;
using namespace fmt;

int main()
{
	// delete element
	{
		// pop_front and pop_back
		list<int> ilist{ 1,2,3,4,5 };
		while (!ilist.empty())
		{
			ilist.pop_back();
			print("after pop_back, ilist : {}\n", ilist);
		}
		ilist = { 1,2,3,4,5 };
		while (!ilist.empty())
		{
			ilist.pop_front();
			print("after pop_back, ilist : {}\n", ilist);
		}
	}
	{
		// erase a single element
		list<int> lst{ 0,1,2,3,4,5,6,7,8,9 };
		auto it = lst.begin();
		while(it != lst.end())
		{
			if (*it % 2)
			{
				it = lst.erase(it);
				print("after erase an odd element, lst is: {}\n", lst);
			}
			else ++it;
		}
		lst = { 0,1,2,3,4,5,6,7,8,9 };
		it = lst.end();
		while(it!=lst.begin())
		{
			--it;
			if (*it % 2)
			{
				it = lst.erase(it);
				print("after erase an odd element, lst is: {}\n", lst);
				print("is it equals .end()?: {}\n", it == lst.end());
			}
		}
	}

	{
		// erase multiple elements
		vector<int> ivec = { 0,1,2,3,4,5,6,7,8,9 };
		// the second iterator is pointed to the next element of the element we want to delete
		// in other word: [first, second);
		// and return the next element to the last deleted element
		auto start = ivec.begin();
		auto end = 3+ start;
		ivec.erase(start, end);
		print("after erase from begin to begin, vec is: {}\n", ivec);
		ivec.clear();
		print("after clear, vec is: {}\n", ivec);
	}
	return 0;
}