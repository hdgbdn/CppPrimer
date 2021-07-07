#include <iostream>
#include <string>

using namespace std;

class Base{
public:
    virtual int fcn() { return 0; }
};

class D1: public Base{
public:
    int fcn(int) { cout << "int D1::fcn(int)" << endl; return 1; };
    virtual int fcn() override { cout << "int D1::fcn()" << endl; return 1; }
    virtual void f2() {}
};

int main()
{
    // 15.23
    // add a same name and parameter and return type as the base one, and add override to specify it's a overrided version
    Base bobj; D1 d1obj;
    Base* bp1 = &bobj, * bp2 = &d1obj;
    bp1->fcn();
    D1* pd1 = &d1obj;
    pd1->fcn();
    pd1->fcn(10);

    bp1->fcn();     // Base version
    bp2->fcn();     // D1 version

    return 0;
}