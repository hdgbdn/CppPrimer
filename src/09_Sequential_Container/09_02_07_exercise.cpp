#include <vector>
#include <iostream>
#include <list>

using namespace std;

int main()
{
	// 9.15
	list<int> il{ 1,2,3,4,5 };
	vector<int> iv{ 1,2,3,4,5 };
	cout << (list<int>(iv.begin(), iv.end()) == il) << endl;

	// 9.16 both have identical container  and element type, and the element defines compare function
}