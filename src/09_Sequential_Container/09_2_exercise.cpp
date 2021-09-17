#include <list>
#include <deque>
#include <iostream>

using namespace std;

int main()
{
	list<deque<int>> l1{{1,2,3}, {3,4,5,6}};
	for(auto dq : l1)
	{
		for (auto i : dq)
		{
			cout << i << ' ';
		}
		cout << endl;
	}
		
}
