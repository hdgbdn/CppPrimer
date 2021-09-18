#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

int main()
{
	// 9.9: begin is a normal iterator, itself can be changed, and the element been pointed to also can be changed
	// cbegin itself can be changed, but the element it pointed to can not be changed;
	{
		vector<int> v1{ 1, 2, 3, 4 };
		auto i = v1.begin();
		auto ci = v1.cbegin();
		*i = 2;
		cout << *i << endl;
		cout << *(++i) << endl;
		cout << *ci << endl;
		// *ci = 2; // error, can not assign to a readonly
	}

	// 9.10
	{
		vector<int> v1;
		const vector<int> v2;
		auto it1 = v1.begin();		// vector<int>::iterator
		auto it2 = v2.begin();		// vector<int>::const_iterator
		auto it3 = v1.cbegin();		// vector<int>::const_iterator
		auto it4 = v2.cbegin();		// vector<int>::const_iterator
	}
	
}