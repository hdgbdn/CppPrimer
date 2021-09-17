#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

int main()
{
	// begin and end member
	list<string> a = { "Milton", "Shakespeare", "Austen" };
	auto it1 = a.begin();		// normal iterator
	auto it2 = a.rbegin();		// reverse one
	auto it3 = a.cbegin();		// const one, means can't change the element, but can change the iterator
	auto it4 = a.crbegin();		// reverse and const one
	
	cout << "list<string>::iterator start" << endl;
	for(; it1 != a.end(); ++it1)
	{
		cout << *it1 << ' ';
	}
	cout << endl << "list<string>::iterator end" << endl;


	cout << "list<string>::reverse_iterator start" << endl;
	for (; it2 != a.rend(); ++it2)
	{
		cout << *it2 << ' ';
	}
	cout << endl << "list<string>::reverse_iterator end" << endl;

	// *it3 = "hi"; // error
}