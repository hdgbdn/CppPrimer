#include "fmt/ranges.h"
#include <vector>
#include <string>
#include <random>
#include <functional>
#include <stack>
#include <queue>

using namespace std;
using namespace fmt;

int main()
{
	{
		// stack and queue are based on deque
		deque<int> deq;
		for (int i = 0; i < 12; ++i)
		{
			deq.push_back(i);
		}
		stack<int> stk(deq);
		print("stack<int> top is {}\n", stk.top());
		// priority_queue is based on vector
	}

	{
		vector<string> svec;
		for (int i = 0; i < 12; ++i)
		{
			svec.push_back(to_string(i));
		}
		stack<string, vector<string>> str_stk2(svec);
		print("stack<string, vector<string>> top is {}\n", str_stk2.top());
	}
	{
		// stack adapter
		stack<int> intStack;
		for (size_t ix = 0; ix != 10; ++ix)
			intStack.push(ix);
		while(!intStack.empty())
		{
			int value = intStack.top();
			print("intStack pop value {}\n", value);
			intStack.pop();
		}
	}
	return 0;
}