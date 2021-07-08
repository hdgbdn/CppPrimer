#include <iostream>
#include <string>

using namespace std;

class Base{
public:
    virtual ~Base(){ cout << "Base::~Base()" << endl;}
};

class Derived: public Base{
public:
    virtual ~Derived(){ cout << "Dervied::~Derived()" << endl; }
};

int main()
{
    // why need virtual destructor
    // because if delete a base pointer which points to a derived object,
    // then if we don't define virtual destructor, then it will use the base destructor
    Base* p = new Derived();
    delete p;
    // output is:
    // Dervied::~Derived()
    // Base::~Base()
    // looks like the base part's destructor is automatically called

    // if class defined it's own copy constructor copy assignment or destructor(even defined deleted!!!!!!!!!!)
    // compiler will not synthesize move constructor
    return 0;
}