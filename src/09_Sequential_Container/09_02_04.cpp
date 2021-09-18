#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <forward_list>
#include <deque>
#include <array>

using namespace std;

class DefaultString
{
public:
	DefaultString(): name("test") {}
	string name;
};

int main()
{
	{
		vector<int> v;
		vector<int> v1(v);
		vector<int> v2 = v;
		vector<int> v3{ 1,2,3,4 };
		vector<int> v4 = { 1,2,3,4 };
		vector<int> v5(v4.begin(), v4.end());

		// only sequence container can accept n (means exclude array)
		vector<int> v6(10);		// since no init value is given, the type must have a accessible default constructor
		vector<int> v7(10, 1);
	}

	{
		list<string> authors = { "Milton", "Shakespeare", "Austen" };
		vector<const char*> articles = { "a", "an", "the" };
		list<string> list2(authors);			// same type, use copy constructor
		// deque<string>  authList(authors);		// not same container type, error
		// vector<string> words(articles);		// not same element type, error
	}

	{
		// new in c11: list initialization
		vector<int> v1{ 1,2,3,4 };			// copy style
		vector<int> v2 = { 1,2,3,4 };		// assign style

		// and specify container's size
		// if element type has default constructor, then can only specify num
		// else have to specify value
		vector<int> ivec(10, -1);
		list<string> svec(10, "hi");
		forward_list<int> iflst(10);
		deque<string> sdeque(10);
	}

	{
		{
			// array is special, because it has fixed size
			// so have to specify size when been constructing
			array<int, 42> ia;
			array<string, 10> sa;
			// since the length is fixed after constructing, there will be filled with default elements
			cout << "test build-int types in std::array" << endl;
			for(auto i : ia)
			{
				// for build-in types, the memory is un-initialized
				cout << i << '\t';
			}
			cout << endl;
		}
		{
			array<DefaultString, 19> sa2;
			cout << "test user types in std::array" << endl;
			for(auto s: sa2)
			{
				cout << s.name << '\t';
			}
			cout << endl;
		}
		{
			cout << "test initialization size of integers in array" << endl;
			array<int, 5> ia{ 1,2 };
			for(auto i : ia)
			{
				// but the un assigned is 0? what's the difference between array<int, 42> ia;?
				// in this situation, the rest element is value-initialized, but the array<int, 42> ia is un-initialized
				cout << i << '\t';
			}
			cout << endl;
		}
		
	}
}