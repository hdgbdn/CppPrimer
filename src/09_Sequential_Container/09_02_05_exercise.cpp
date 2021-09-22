#include <list>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	list<const char*> charList{ "a", "b", "c" };
	vector<string> sVec;
	sVec.assign(charList.cbegin(), charList.cend());
	for(auto s : sVec)
	{
		cout << s << endl;
	}
}