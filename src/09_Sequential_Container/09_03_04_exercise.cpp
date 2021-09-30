#include "fmt/ranges.h"
#include <forward_list>
#include <string>
#include <functional>

using namespace std;
using namespace fmt;

int main()
{
	{
		// 9.27
		forward_list<int> lst{ 1,231,4124,523,534,1,1234,123,123,59,79787,7979,7907 };
		auto prev = lst.before_begin();
		auto curr = lst.begin();
		while (curr != lst.end())
		{
			if(*curr % 2 != 0)
			{
				curr = lst.erase_after(prev);
			}
			else
			{
				prev = curr;
				++curr;
			}
		}
		print("deleted all odd elements: {}\n", lst);
	}

	{
		// 9.28
		auto f = [](forward_list<string>& lst, const string& s1, const string& s2)
		{
			auto curr = lst.begin();
			auto prev = lst.before_begin();
			while(curr != lst.end())
			{
				if (*curr == s1)
				{
					prev = curr;
					++curr;
					break;
				}
				else
				{
					prev = curr;
					++curr;
				}
			}
			lst.insert_after(prev, s2);
		};
		forward_list<string> lst1{ "a", "c", "d", "e"};
		forward_list<string> lst2{ "a", "b" };
		f(lst1, "a", "b");
		f(lst2, "e", "c");
		print("list 1 is : {}\n", lst1);
		print("list 2 is : {}\n", lst2);

	}
	return 0;
}