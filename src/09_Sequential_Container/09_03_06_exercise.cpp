#include "fmt/ranges.h"
#include <vector>
#include <list>
#include <forward_list>

using namespace std;
using namespace fmt;

int main()
{
	{
		// 9.31
		// because list can't move iterator by step
		forward_list<int> lst = { 0,1,2,3,4,5,6,7,8,9 };
		auto prev = lst.before_begin();
		auto curr = lst.begin();
		while (curr != lst.end())
		{
			if (*curr % 2)
			{
				curr = lst.insert_after(curr, *curr);
				prev = curr;
				++curr;
			}
			else
			{
				curr = lst.erase_after(prev);
			}
		}
		print("9.3.1:duplicate odd, delete even {} \n", lst);
	}
	{
		// 9.32
		vector<int> vi = { 0,1,2,3,4,5,6,7,8,9 };
		auto iter = vi.begin();
		while (iter != vi.end())
		{
			if (*iter % 2)
			{
				iter = vi.insert(iter, *iter);
				// illegal, because iter may be end();
				// and execution order of parameter may differ between compiler
				iter += 2;	// end() += 2 still end?
			}
			else
			{
				iter = vi.erase(iter);
			}
		}
		print("9.3.2:duplicate odd, delete even {} \n", vi);
	}
	{
		// 9.33
		vector<int> ivec{ 1,2,3,4 };
		auto begin = ivec.begin();
		while (begin != ivec.end())
		{
			++begin;
			begin = ivec.insert(begin, 999);
			// after insertion, new memory may be allocated, and original iterator may be need update
			++begin;
		}
		print("9.3.3:{} \n", ivec);
	}
	return 0;
}