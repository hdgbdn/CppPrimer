#include <iostream>
#include <vector>
#include <list>
#include <functional>

using namespace std;

int main()
{
	// 9.3: begin <= end; and point to the same container

	// 9.4
	auto f1 = [](vector<int>::const_iterator begin, vector<int>::const_iterator end, int i)->bool
	{
		while(begin != end)
		{
			if (*begin == i) return true;
			++begin;
		}
		return false;
	};
	vector<int> v1 = { 1,2,3,4,5,6,7,8 };
	vector<int> v2 = { 2,3,4,5,6,7,8,9 };
	const int des = 1;
	cout << "v1 found " << des << ' ' << f1(v1.begin(), v1.end(), des) << endl;
	cout << "v2 found " << des << ' ' << f1(v2.begin(), v2.end(), des) << endl;

	// 9.5
	auto f2 = [](vector<int>::const_iterator begin, vector<int>::const_iterator end, int i)->vector<int>::const_iterator
	{
		while (begin != end)
		{
			if (*begin == i) return begin;
			++begin;
		}
		return end;
	};
	if (f2(v1.begin(), v1.end(), des) != v1.end()) cout << "v1 found " << des << endl;
	if (f2(v2.begin(), v2.end(), des) != v2.end()) cout << "v2 found " << des << endl;

	// 9.6
	list<int> lst1;
	auto iter1 = lst1.begin(), iter2 = lst1.end();
	// while (iter1 < iter2) { ++iter1; } // list iterator don't support operator<, because list is link by pointer, and can't compare position;
}