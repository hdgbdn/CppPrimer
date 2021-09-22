#include <vector>
#include <list>

using namespace std;

int main()
{
	// 9.11
	{
		vector<int> ivec1;
		vector<int> ivec2(10);
		vector<int> ivec3(10, 1);
		vector<int> ivec4{ 10 };
		vector<int> ivec5(ivec1);
		vector<int> ivec6 = ivec1;
		vector<int> ivec7(ivec1.begin(), ivec1.end());
	}
	// 9.12
	{
		vector<int> ivec{ 1,2,3,4 };
		vector<int> ivec2(ivec);		// ok
		// vector<float> fvec1(ivec);		// error, different element type;
		// list<int> ilist1(ivec);			// error, different container type
		vector<float> fvec2(ivec.begin(), ivec.end());	// but use iterator can
		list<int> ilist1(ivec.begin(), ivec.end());		// also can
	}
	// 9.13
	{
		// use iterator to init
		list<int> ilist{ 1,2,3,4,5,6 };
		vector<int> ivec{ 1,2,3,4,5,6 };
		vector<double> dvec1(ilist.begin(), ilist.end());
		vector<double> dvec2(ivec.begin(), ivec.end());
	}
}