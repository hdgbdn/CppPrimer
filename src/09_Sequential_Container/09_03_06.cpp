#include "fmt/ranges.h"
#include <vector>
#include <deque>

using namespace std;
using namespace fmt;

int main()
{

	{
		// for adding elements
		//
		// vector and string after re-allocate memory, then the iterator, pointer reference to the container will be invalid
		vector<int> ivec{ 1,2,3,4 };
		auto begin = ivec.begin();
		print("the begin iterator's value is: {}\n", *begin);
		ivec.resize(2);
		print("after shrink, the begin iterator's value is: {}\n", *begin);	// shrink is okay, because don't allocate new memory
		ivec.resize(20);
		// print("after expand, the begin iterator's value is: {}\n", *begin); // runtime error, because allocated new memory

		// deque, any operation except inserting into head and end will cause iterator, pointer reference to the container invalid;
		deque<int> ideque{ 1,2,3,4 };
		
		// balabalabala too complicate to memory, so just remember that after adding or deleting elements,
		// the iterator, pointer and reference you kept may be invalid
	}
	
	{
		// for loops that changes container
		// make sure in every loop, update pointer reference and iterator

		vector<int> vi = { 0,1,2,3,4,5,6,7,8,9 };
		auto iter = vi.begin();
		while(iter != vi.end())
		{
			if (*iter % 2)
			{
				iter = vi.insert(iter, *iter);
				iter += 2;
			}
			else
			{
				iter = vi.erase(iter);
			}
		}
		print("duplicate odd, delete even {} \n", vi);
	}
	{
		// don't keep the iterator that end() returns
		vector<int> vi = { 0,1,2,3,4,5,6,7,8,9 };
		auto begin = vi.begin(), end = vi.end();
		/*while(begin != end)
		{
			++begin;
			vi.insert(begin, 42);
			++begin;
			print("after inserting 42 {} \n", vi);
		}*/
	}
	return 0;
}