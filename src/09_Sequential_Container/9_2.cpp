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
}
