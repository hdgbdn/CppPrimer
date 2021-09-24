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
		// push back
		string word;
		vector<string> svec;
	/*	while(cin >> word)
		{
			svec.push_back(word);
		}
		for(auto w : svec)
		{
			cout << w << endl;
		}*/
		// the element in container is a copy of origin element
	}
	{
		// push_front
		// only for list forward_list and deque
		list<string> sl;
		forward_list<string> sfl;
		deque<string> sd;
		vector<string> sv;
		sl.push_front("a");
		sfl.push_front("a");
		sd.push_front("a");
		// sv.push_front("a"); // vector has no push_front member
		// push_front is only for list, not array
	}
	{
		// insert: can insert element before the given iterator
		list<string> sl;
		forward_list<string> sfl;
		deque<string> sd;
		vector<string> sv;
		// 1. insert with iterator and element
		sl.insert(sl.begin(), "a");
		// sfl.insert(sfl.begin(), "a"); // forward list has no insert member
		sd.insert(sd.begin(), "a");
		sv.insert(sv.begin(), "a");
		// 2. with iterator and nums
		sl.insert(sl.begin(), 10, "hi");
		// 3. with pair of iterator
		sd.insert(sd.end(), sl.begin(), sl.end());
		// 4. with list
		sd.insert(sd.end(), { "a", "b", "c" });
	}
	{
		// use return value of insert
		// since insert returns the begin of the new inserted elements
		string word;
		list<string> list;
		auto iter = list.begin();
		//while(cin >> word)
		//{
		//	iter = list.insert(iter, word);
		//}
		//cout << "use return value of insert" << endl;
		//for (auto w : list)
		//{
		//	cout << w << '\t';
		//}
		cout << endl;
	}
	{
		// emplace
		// more effective than push_back
		// directly construct element, different from push_back: it don't create temp object
		list<string> list;
		list.emplace(list.begin(), "a");
	}
	return 0;
}