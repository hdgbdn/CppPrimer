#include "fmt/ranges.h"
#include <vector>

using namespace std;
using namespace fmt;

int main()
{
	{
		vector<int> ivec;
		for (int i = 0; i < 20; ++i)
		{
			ivec.push_back(1);
			print("{} : capacity is:{} \n", ivec, ivec.capacity());
			print("{} : size is:{} \n", ivec, ivec.size());
		}
	}
	{
		vector<int> ivec;
		for(int i = 0; i < 20; ++i)
		{
			ivec.push_back(1);
			print("{} : capacity is:{} \n", ivec, ivec.capacity());
			print("{} : size is:{} \n", ivec, ivec.size());
			ivec.shrink_to_fit();
			print("{} :after shrink, capacity is:{} \n", ivec, ivec.capacity());
			print("{} :after shrink, size is:{} \n", ivec, ivec.size());
		}
	}
	{
		// resize and reverse
		vector<int> ivec{1};
		ivec.reserve(20);
		print("after reserve to 20, the capacity is: {} \n", ivec.capacity());
		ivec.resize(12, 23);
		print("after resize(12, 23), the capacity is: {}, and vector is: {} \n", ivec.capacity(), ivec);
		ivec.resize(2, 100);
		print("after resize(2, 100), the capacity is: {}, and vector is: {} \n", ivec.capacity(), ivec);
	}
}