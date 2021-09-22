#include <vector>
#include <array>
#include <list>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	{
		vector<int> ivec1{ 1,2,3,4,5 };
		vector<int> ivec2{ 1,2,3 };
		vector<int> ivec3;
		cout << "before assign, ivec3 size is " << ivec3.size()
			<< " capacity is " << ivec3.capacity() << endl;
		ivec3 = ivec1;
		cout << "after assign { 1,2,3,4,5 }, ivec3 size is " << ivec3.size()
			<< " capacity is " << ivec3.capacity() << endl;
		ivec3 = ivec2;
		cout << "after assign { 1,2,3 }, ivec3 size is " << ivec3.size()
			<< " capacity is " << ivec3.capacity() << endl;

		// array can't use {}
		// but it is legal now?
		array<int, 10> iarr1;
		iarr1 = { 1,23,4 };
	}

	{
		// use assign
		list<string> names;
		vector<const char*> oldstyle{ "a", "b", "c", "d" };
		// like use iterator to initialize
		names.assign(oldstyle.cbegin(), oldstyle.cend());
		// another usage
		list<string> ls{ "a", "b", "c", "d" };
		ls.assign(10, "b");
		for (auto s :ls)
		{
			cout << s << '\t';
		}
		cout << endl;
	}

	{
		// swap
		vector<string> svec1(10);
		vector<string> svec2(20);
		swap(svec1, svec2);
		cout << "svec2 size after swap: " << svec2.size() << endl;	// 10

		// swap is fast because it only changes the element position,
		// but array is really change the elements
		list<string> slist1{ "a" };
		list<string> slist2{ "b" };
		auto ilist1 = slist1.begin();
		swap(slist1, slist2);
		cout << "after swapping, the slist1.begin() is: " << *ilist1 << endl;	// still a
		array<string, 1> sarr1{ "a" };
		array<string, 1> sarr2{ "b" };
		auto iarr1 = sarr1.begin();
		swap(sarr1, sarr2);
		cout << "after swapping, the sarr1.begin() is: " << *iarr1 << endl;	// becomes b
	}
	
}