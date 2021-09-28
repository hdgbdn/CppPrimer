#include "fmt/core.h"
#include <vector>

using namespace std;
using namespace fmt;

int main()
{
	{
		// 9.23
		vector<int> c{ 1 };
		if(!c.empty())
		{
			auto val = *c.begin(), val2 = c.front();
			auto last = c.end();
			auto val3 = *(--last);
			auto val4 = c.back();
			print("val: {}, val2: {}, val3 {}, val4 {} \n", val, val2, val3, val4);
		}
	}

	{
		// 9.24
		vector<int> v;
		// don't throw exception when use operator[]
		/*try
		{
			auto i = v[0];
		}
		catch (const exception& e)
		{
			print("exception happened when v[0]: {} ", e.what());
		}*/
		try
		{
			auto i = v.at(0);
		}
		catch (const exception& e)
		{
			print("exception happened when v.at(0): {} ", e.what());
		}

		// don't throw exception when use .front()
		/*try
		{
			auto i = v.front();
		}
		catch (const exception& e)
		{
			print("exception happened when v.front(): {} ", e.what());
		}*/

		// don't throw exception when use *.begin();
		try
		{
			auto i = *v.begin();
		}
		catch (const exception& e)
		{
			print("exception happened when *v.begin(): {} ", e.what());
		}
	}
	
	
}