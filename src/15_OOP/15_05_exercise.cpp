#include <iostream>
#include <string>

using namespace std;

class Base {
public:
    virtual void pub_mem() { cout << "Base's pub function" << endl; }
protected:
    int prot_mem;
private:
    char priv_mem;
};

struct Pub_Derv : public Base{
    void memfcn(Base &b) { b = *this; }
    virtual void pub_mem() override { cout << "Pub_Derv's pub function" << endl; }
    int f() { return prot_mem; }
};

struct Priv_Derv : private Base{
    void memfcn(Base &b) { b = *this; }
    friend void Friend_Call_pubmem(Base&);
    virtual void pub_mem() override { cout << "Priv_Derv's pub function" << endl; }
    int f1() const { return prot_mem; }
};

struct Prot_Derv : protected Base{
    void memfcn(Base &b) { b = *this; }
    virtual void pub_mem() override { cout << "Prot_Derv's pub function" << endl; }
    int f1() const { return prot_mem; }
};

struct Derived_from_Public : public Pub_Derv{
    void memfcn(Base &b) { b = *this; }
    int use_base() { return prot_mem; }             // correct, the Base's public is still public in Pub_Derv
};

struct Derived_from_Private : public Priv_Derv{
    // void memfcn(Base &b) { b = *this; }          // error C2247: 'Base' not accessible because 'Priv_Derv' uses 'private' to inherit from 'Base'
    // int use_base() { return prot_mem; }             // error: the private inherited member: prot_mem is private in Priv_Derv
};

struct Derived_from_Protected : public Prot_Derv{
    void memfcn(Base &b) { b = *this; }
    int use_base() { return prot_mem; }             // correct, the protected inherited member: prot_mem is protected in Prot_Derv
};

//----------------------
class Shape{
public:
    virtual void Draw() = 0;
};

class Cube : public Shape{

};

class Circle : public Shape{

};

class Sphere : public Shape{

};

int main()
{
    // 15.18
    Pub_Derv d1;
    Priv_Derv d2;
    Prot_Derv d3;
    Derived_from_Public dd1;
    Derived_from_Private dd2;
    Derived_from_Protected dd3;
    Base* p = &d1;
    //p = &d2;            // the Base part is inaccessible, it is private
    //p = &d3;            // the Base part is inaccessible, it is protected
    p = &dd1;           // correct, the Base part is public.
    //p = &dd2;           // the Base part is inaccessible, it is private
    //p = &dd3;           // the Base part is inaccessible, it is protected

    // 15.19
    // void memfcn(Base &b) { b = *this; }
    // Pub_Derv: legal, the Base part is: public
    // Priv_Derv: legal, the Base part is: private, still accessible
    // Prot_Dery: legal, the Base part is: protected, still accessible
    // Derived_from_Public: legal, the Base part is public
    // Derived_from_Private: illegal, the Base part is private in Priv_Derv, so Derived_from_Private can't access 
    // Derived_from_Protected: legal, the Base part is: protected in Prot_Derv, so Derived_from_Protected can access 

    // 15.20
    // correct

    // 15.21

    return 0;
}