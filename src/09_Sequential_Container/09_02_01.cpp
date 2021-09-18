#include <iostream>
#include <vector>

class noDefault
{
public:
    noDefault() = delete;
    noDefault(int a) {}
};

using namespace std;

int main()
{
    // for some classes that don't have default constructor, can't init container only with count
    vector<noDefault> v1(10, 2);
    //vector<noDefault> v2(10);     // error, try to access a deleted function

    // iterators
    // [begin, end)
    // why left close right open?
    // 1.if begin == end, then then range is empty
    vector<int> v2;
    if (v2.begin() == v2.end()) cout << "v2 range is empty" << endl;
    // 2. if begin != end, then the range must have at least one element, and begin is pointed to the first element
    v2.push_back(1);
    if (v2.begin() != v2.end()) cout << "v2's first element is " << *v2.begin() << endl;
    // 3. and we can add begin until begin == end
    auto begin = v2.begin();
    auto end = v2.end();
    while (begin != end) cout << "v2's element " << *(begin++) << endl;
    // if end is close [begin, end], then when begin == end, we still don't know if we reach the end, begin == end + 1, is not elegant
}
