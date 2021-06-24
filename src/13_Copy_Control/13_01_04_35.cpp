#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

int main()
{
    // first, make sure whether class needs destructor
    // if needs a destructor, then it should need a copy constructor and a copy assignment
    // because, a manual destructor means there are members that need manulay destroy
    // an example:
    class HasPtr{
    public:
        HasPtr(const string &s = string()):
            ps(new string(s)), i(0) {}
        ~HasPtr() {delete ps;}
    private:
        string* ps;
        int i;
    };
    return 0;

    // HasPtr uses a synthesized copy constructor and copy assignment
    // it just copies the pointer, so all the pointer shares the same memory

    auto f = [](HasPtr hp)->HasPtr{
        HasPtr ret = hp;
        return ret;     // after leaving f, hp will delete the string*, sinece ret shares the same memory, the string* in ret becomes dangling
    };

    // second, a class needs copy constructor also needs assignment
    // 
    class CopyCount{
    public:
        int count;
        CopyCount(int c = 0): count(c) {}
        CopyCount(const CopyCount& cc) {count = cc.count + 1;}
        CopyCount& operator=(const CopyCount& rhs) {count = rhs.count + 1; return *this;}
    };
}