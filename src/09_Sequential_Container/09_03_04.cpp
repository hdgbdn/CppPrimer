#include "fmt/ranges.h"
#include <forward_list>

using namespace std;
using namespace fmt;

int main()
{
	{
		// why forward_list is special, because it is a linked-list, so it is impossible to find a node's before
		// so it has before_begin, insert_after
		forward_list<int> flst = { 0,1,2,3,4,5,6,7,8,9 };
		auto prev = flst.before_begin();
		auto curr = flst.begin();
		while (curr != flst.end())
		{
			if (*curr % 2)
			{
				curr = flst.erase_after(prev);
			}
			else
			{
				prev = curr;
				++curr;
			}
			print("flst now is {\n", flst);
		}
	}
}