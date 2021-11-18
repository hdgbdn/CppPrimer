#include "fmt/ranges.h"
#include <string>
#include <functional>
#include <stack>

using namespace std;
using namespace fmt;

int main()
{
	stack<string> stk;
	function<void(const string&)> removeParenthesis = [&](const string& input)
	{
		if (input.empty()) return;
		auto pStartPos = input.find('(');
		auto pEndPos = input.find(')');
		if(pStartPos == string::npos) 
			stk.push(input);
		else
		{
			removeParenthesis(input.substr(0, pStartPos ));
			removeParenthesis(input.substr(pStartPos + 1, pEndPos - pStartPos - 1));
			removeParenthesis(input.substr(pEndPos + 1, input.size() - pEndPos));
		}
	};

	string test = "i am(a)( boy)((but))";
	removeParenthesis(test);
	while(!stk.empty())
	{
		auto top = stk.top();
		print("in stack is: {}\n", top);
		stk.pop();
	}
	return 0;
}