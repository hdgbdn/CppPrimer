#include <iostream>
#include <string>

using namespace std;

class Base{
public:
    Base(): mem(0) {}
    int mem;
    void fun() {};
    virtual void vfunc(){ cout << "Base::vfunc()" << endl; }
};

class Dervied : public Base{
public:
    Dervied() = default;
    Dervied(int i): mem(i) {}
    int get_mem(){ return mem; }
    int get_base_mem() { return Base::mem; }
    int dervide_mem;
    void fun(int) {};
    void vfunc(int) {};
protected:
    int mem;
};

class D1: public Base{
public:
    void vfunc(int) { cout << "D1::vfunc()" << endl; }
    void func2() {cout << "D1::func2()" << endl; }
};

class D2: public D1{
public:
    void vfunc(int) { cout << "D2::vfunc(int)" << endl; }
    void vfunc() { cout << "D2::vfunc()" << endl; }
    void func2() { cout << "D2::func2()" << endl; }
};

int main()
{
    // 1. derived classes' scope is still in the same scope of base class
    // for example: derived.mem()
    // first find mem() in derived, if not found
    // find mem() upwards, untill find it, then stop

    // what members we can find is depend on the static type
    Base b;
    Dervied d;
    Base *bp = &d;
    Dervied *dp = &d;
    // bp->dervide_mem;        // 'dervide_mem': is not a member of 'Base'
    dp->dervide_mem;

    // derived can override names
    Dervied d2(42);         // init derived's mem
    cout << d2.get_mem() << endl;       // 42, not 0
    // but also can use a hidden base member
    cout << d2.get_base_mem() << endl;  // 0
    
    // summary:
    // first, the callers static type.
    // then find mem in the static type's scope,
    // if can't find, then find upwards until find,
    // or compiler will throw error
    // if find mem, then just common check the parameter and return type, if passed
    // check if mem is virtual, if is vitual than call the function based on the dynamic type
    // else if not virtual just call the function

    // name is prefered than type
    // so if defined a same name member in derived class, it will override the base one,
    // but base one is still exist, and can be called like: base::mem
    // and it just by their name
    {
        Base b; Dervied d;
        b.fun();
        d.fun(10);
        // d.fun();         // illegal: the void fun() if overrided by void Dervied::fun(int)
        d.Base::fun();
    }

    // virtual function and scope
    // so that explained why virtual functions should have same parameters
    // because the same name function will override the virtual one
    {
        Dervied d;
        Base* pb = &d;
        pb->vfunc();         // Base::vfunc: since static type is Base, so search Base's vfunc
        Dervied* pd = &d;
        // pd->vfunc();        // error: the Base::vfunc() was hidden by the Derived's same name function
    }

    // summary
    {
        Base bobj; D1 d1obj; D2 d2obj;

        Base* bp1 = &bobj, *bp2 = &d1obj, *bp3 = &d2obj;
        cout << "summary" << endl;
        bp1->vfunc();       // Base::vfunc
        bp2->vfunc();       // Base::vfunc
        bp3->vfunc();       // D2::vfunc    override Base's virtual function

        D1* d1p = &d1obj; D2* d2p = &d2obj;
        // bp2->fun2()      // error: bp2's static type is Base, fun2 is not in that scope
        d1p->func2();       // D1::func2
        d2p->func2();       // D2::func2

        Base* p1 = &d2obj; D1* p2 = &d2obj; D2* p3 = &d2obj;
        // p1->vfunc(12);   // error, Base don't have a vfunc accpets int as parameter
        p2->vfunc(10);      // static binding, D1::vfunc(10);
        p3->vfunc(10);      // static binding, D2::vfunc(10);
    }

    return 0;
}