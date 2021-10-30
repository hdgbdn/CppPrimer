#include "fmt/ranges.h"
#include <vector>
#include <string>
#include <random>
#include <functional>

using namespace std;
using namespace fmt;

int main()
{
	{
		// 9.47
		string letters;
		for (int i = 0; i <= 'z' - 'a'; ++i)
			letters.push_back('a' + i);
		for (int i = 0; i <= 'Z' - 'A'; ++i)
			letters.push_back('A' + i);
		print(letters);
		string numbers = "1234567890";
		string target = "ab2c3d7R4E6";
		string::size_type i = 0;
		while ((i = target.find_first_of(letters, i)) != string::npos)
		{
			print("find letter using find_first_of in pos {}, letter is {}\n", i, target[i]);
			++i;
		}
		i = 0;
		while ((i = target.find_first_of(numbers, i)) != string::npos)
		{
			print("find number using find_first_of in pos {}, number is {}\n", i, target[i]);
			++i;
		}
		i = 0;
		while ((i = target.find_first_not_of(numbers, i)) != string::npos)
		{
			print("find letter using find_first_not_of in pos {}, letter is {}\n", i, target[i]);
			++i;
		}
		i = 0;
		while ((i = target.find_first_not_of(letters, i)) != string::npos)
		{
			print("find number using find_first_not_of in pos {}, number is {}\n", i, target[i]);
			++i;
		}
	}
	{
		// 9.48
		string nubmers("0123456789"), name("r2d2");
		auto pos = nubmers.find(name);
		print("found name in numbers: {}\n", pos != string::npos);
	}
	{
		// 9.49
		string ascenderDescender("bdfhijkltgjqpy");
		for(int i = 0; i < 20; ++i)
		{
			string test;
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_int_distribution<int> dist(0, 25);
			for(int j = 0; j < 8; ++j)
			{
				test.push_back('a' + dist(mt));
			}
			string::size_type retPos = 0;
			string::size_type retLen = 0;
			string::size_type curPos = 0;
			while(curPos != string::npos)
			{
				auto start = test.find_first_not_of(ascenderDescender, curPos);
				auto end = test.find_first_of(ascenderDescender, start);
				if (start != string::npos )
				{
					if(end == string::npos)
					{
						end = test.size();
					}
					auto curLen = end - start;
					if(curLen > retLen)
					{
						retPos = start; retLen = curLen;
					}
				}
				curPos = end == string::npos ? end : end + 1;
			}

			print("{}: the longest subsequence without ascender and descender is: {}\n", test, test.substr(retPos, retLen));
		}
	}
	return 0;
}