#include "fmt/ranges.h"
#include <vector>
#include <string>

using namespace std;
using namespace fmt;

int main()
{
	// 9.41
	vector<char> cv{ '1','2','3' };
	string s(cv.begin(), cv.end());
	print(s);

	// 9.42
	// reserve 110
	return 0;
}