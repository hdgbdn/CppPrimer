#include "fmt/ranges.h"
#include <vector>
#include <string>
#include <functional>

using namespace std;
using namespace fmt;

int main()
{
	{
		// 9.43
		auto replaceFunc = [](string& s, const string& oldVal, const string& newVal)
		{
			auto iter = s.begin();
			while(iter < s.end() - oldVal.size() + 1)
			{
				string cur{ iter, iter + oldVal.size() };
				if (cur == oldVal)
				{
					iter = s.erase(iter, iter + oldVal.size());
					iter = s.insert(iter, newVal.begin(), newVal.end());
					iter += newVal.size();
				}
				else
					++iter;
			}
		};
		string s1 = "hi thotho, tho, ni haothotho";
		replaceFunc(s1, "tho", "though");
		print(s1 + '\n');
	}
	{
		// 9.44
		auto replaceFunc = [](string& s, const string& oldVal, const string& newVal)
		{
			for(int i = 0; i < s.size() - oldVal.size() + 1; ++i)
			{
				string cur(s, i, oldVal.size());
				if (cur == oldVal)
				{
					s.replace(i, oldVal.size(), newVal);
					i += newVal.size() - 1;
				}
					
			}
		};
		string s1 = "hi thotho, tho, ni haothotho";
		replaceFunc(s1, "tho", "though");
		print(s1 + '\n');
	}
	{
		// 9.45
		auto addPreSuffix = [](string& name, const string& pre, const string& suff)
		{
			name.insert(name.begin(), pre.begin(), pre.end());
			name.append(suff);
		};
		string s1 = "Hu";
		addPreSuffix(s1, "Mr.", "Jr.");
		print(s1 + '\n');

	}
	{
		// 9.46
		auto addPreSuffix = [](string& name, const string& pre, const string& suff)
		{
			name.insert(0, pre);
			name.insert(name.size(), suff);
		};
		string s1 = "Hu";
		addPreSuffix(s1, "Mr.", "Jr.");
		print(s1 + '\n');
	}
	return 0;
}