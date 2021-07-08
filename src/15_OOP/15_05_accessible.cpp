#include <iostream>
#include <string>

using namespace std;

class Pal;

// use base:: to access base's protected member
class MyBase{
friend class Pal;
protected:
    int prot_mem;
private:
    int pri_mem;
};

class Sneaky : public MyBase{
    friend void clobber(Sneaky&);
    friend void clobber(MyBase&);
    int j;
};

void clobber(Sneaky& s) { s.j = s.prot_mem = 0; }
// void clobber(MyBase& b) { b.prot_mem = 0; }           // 'MyBase::prot_mem': cannot access protected member declared in class 'MyBase'

class Pal{
public:
    int f(MyBase b) { return b.prot_mem; }
    // int f2(Sneaky s) { return s.j; }            // error: Pal is not Sneaky's friend, although Sneaky is inherited from MyBase
    int f3(Sneaky s) { return s.prot_mem; }        // but it's ok to access derived class's base part
};

class D2 : public Pal{
public:
    // int mem(MyBase b){ return b.prot_mem; }      // friend can't inherit
};

class MyDerived : private MyBase{
public:
    // using MyBase::pri_mem;       // pri_mem is unaccessible in MyDerived because it's private in MyBase
    using MyBase::prot_mem;         // but protected is accessible, so we can promote it
};

// public private and protected derivation
class Base {
public:
    virtual void pub_mem() { cout << "Base's pub function" << endl; }
protected:
    int prot_mem;
private:
    char priv_mem;
};

struct Pub_Derv : public Base{
    virtual void pub_mem() override { cout << "Pub_Derv's pub function" << endl; }
    int f() { return prot_mem; }
};

struct Priv_Derv : private Base{
    friend void Friend_Call_pubmem(Base&);
    virtual void pub_mem() override { cout << "Priv_Derv's pub function" << endl; }
    int f1() const { return prot_mem; }
};

struct Prot_Derv : protected Base{
    virtual void pub_mem() override { cout << "Prot_Derv's pub function" << endl; }
    int f1() const { return prot_mem; }
};

struct Derived_from_Public : public Pub_Derv{
    int use_base() { return prot_mem; }             // correct, the Base's public is still public in Pub_Derv
};

struct Derived_from_Private : public Priv_Derv{
    // int use_base() { return prot_mem; }             // error: the private inherited member: prot_mem is private in Priv_Derv
};

struct Derived_from_Protected : public Prot_Derv{
    int use_base() { return prot_mem; }             // correct, the protected inherited member: prot_mem is protected in Prot_Derv
};

void Call_pubmem(Base& obj){
    obj.pub_mem();
}

void Friend_Call_pubmem(Base& obj){
    obj.pub_mem();
}

int main()
{
    // protected member
    // can access by derived class, but can't be accessed by other user;
    // for derived class and friend, it works just like a public

    // see the Base and Sneaky above:
    // if a derived class's friend can access a base object's protected member, then if we want to access a class's protected member
    // we just simply derived a class and add a friend to the derived class.
    // so a derived class's friend can only access the derived objects's protected base member, not a base object's protected base member.
    // and a dervied's friend is not the derived's base's friend

    // public private and protected derivation
    // first, derive access specifiers don't affect derived or friend's accessibility of the base member 
    // but for the derived classes' user:
    // public: same as base class
    // protected: all member inherited from base will become protected
    // private: all member inherited from base will become private

    Pub_Derv d1;
    Priv_Derv d2;
    d1.pub_mem();               // correct: public still be public
    // d2.pub_mem();            // error C2247:'Base::pub_mem' not accessible because 'Priv_Derv' uses 'private' to inherit from 'Base'
    Prot_Derv d3;
    // d3.pub_mem();            // error C2247:'Base::pub_mem' not accessible because 'Prot_Derv' uses 'protected' to inherit from 'Base'

    // what about classes inherited from derived class? 
    // see Derived_from_Public, Derived_from_Private, Derived_from_Private above

    // derived-to-base
    // !!!!!!!!!!!!!!importance, a base pointer can't point to a dervied object, if the derived class hide the base part
    // only valid for public inheritance
    Pub_Derv pubD;
    Priv_Derv priD;
    Prot_Derv prtD;
    Base *p = &pubD;              // dervied-to-base: under public inheritance is ok
    cout << "pubic derived to base "; p->pub_mem();
    // *p = &priD;                // binary '=': no operator found which takes a right-hand operand of type 'Priv_Derv *'
    // *p = &prtD;                // binary '=': no operator found which takes a right-hand operand of type 'Prot_Derv *'

    // how about dynamic binding? 
    Call_pubmem(pubD);
    // Call_pubmem(priD);      // error C2243: 'type cast': conversion from 'Priv_Derv *' to 'Base &' exists, but is inaccessible
    // Call_pubmem(prtD);      // error C2243: 'type cast': conversion from 'Prot_Derv *' to 'Base &' exists, but is inaccessible

    // it's simple: the base part is inaccessible in private and protected inheritance

    // friend and inheritance
    // See MyBase, Pal, D2 above
    // friend can't inherite

    // change member's accessibility
    MyDerived md;
    md.prot_mem;

    return 0;
}