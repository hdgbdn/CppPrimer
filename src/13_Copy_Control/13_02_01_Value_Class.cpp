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

// copy-assignment combines destructor and constructor:
// destroy left object, and reconstruct with the right object
// it's very important to handle self-assignment!
// so first to copy the value, then destory
HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
    auto newp = new string(*rhs.ps);
    delete ps;
    ps = newp;
    i = rhs.i;
    return *this;
}

HasPtr::~HasPtr()
{
    delete ps;
}

int main()
{
    
    return 0;
}