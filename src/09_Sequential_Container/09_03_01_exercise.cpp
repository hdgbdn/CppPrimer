#include <vector>
#include <string>
#include <list>
#include <forward_list>
#include <deque>
#include <iostream>

using namespace std;

int main()
{
	{
		// 9.18
		string word;
		deque<string> d;
		while (cin >> word)
			d.push_back(word);
		for (auto w : d) cout << w << '\t';
		cout << endl;
	}
	{
		// 9.19
		string word;
		list<string> l;
		while (cin >> word)
			l.push_back(word);
		for (auto w : l) cout << w << '\t';
		cout << endl;
	}
	{
		// 9.20
		list<int> l{ 1, 3, 4, 23, 44 };
		deque<int> odd;
		deque<int> even;
		for (auto i : l)
			(i & 0x01 ? odd : even).push_back(i);
	}
	{
		// 9.21
		vector<string> svec;
		string word;
		auto iter = svec.begin();
		while (cin >> word)
			iter = svec.insert(iter, word);
	}
	{
		// 9.22
		// the iter don't increase in the loop
		// and mid may became invalid
		// https://stackoverflow.com/questions/6438086/iterator-invalidation-rules-for-c-containers
	}
}