#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

class HasPtr
{
public:
    HasPtr(const string &s = string()) : ps(new string(s)), i(0) {}
    HasPtr(const HasPtr &ptr) : ps(new string(*ptr.ps)), i(ptr.i) {}
    HasPtr& operator=(const HasPtr& rhs);
    ~HasPtr();
    
    const std::string &get() const { return *ps; }
    void set(const std::string &s) { *ps = s; }
private:
    string *ps;
    int i;
};

HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
    // wrong!
    delete ps;
    ps = new string(*rhs.ps);
    i = rhs.i;
    return *this;
}

HasPtr::~HasPtr()
{
    delete ps;
}

int main()
{
    HasPtr p1("p1");
    HasPtr p2(p1);
    HasPtr p3;
    p3 = p2;
    p3.set("p3");
    p2.set("p2");
    cout << "p1 is " << p1.get() << endl;
    cout << "p2 is " << p2.get() << endl;
    cout << "p3 is " << p3.get() << endl;

    return 0;
}