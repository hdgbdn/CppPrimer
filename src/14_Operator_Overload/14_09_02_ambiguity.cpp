#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

struct B;
struct A{
    A() = default;
    A(const B&) {};
};

struct B{
    operator A() const { return A(); };
};

A f(const A&){
    return A();
}

struct C{
    C(int = 0) {};
    C(double) {};
    operator int() const { return int(); };
    operator double() const { return double(); };
};

void f2(long double){
    return;
}

//----------------------
struct D{
    D(int) {}
};

struct E {
    E(int) {}
};

struct F {
    F(double) {}
};

void manip2(const D&){
    cout << "manip2: class D version" << endl;
    return;
}

void mainip2(const E&){
    cout << "mainip2: class E version" << endl;
    return;
}

void mainip3(const E&){
    cout << "mainip3: class E version" << endl;
    return;
}

void mainip3(const F&){
    cout << "mainip3: class F version" << endl;
    return;
}

int main()
{
    // 2 situations that cause ambiguity

    // 1: more than one possible conversion
    B b;
    // A a = f(b);         // error: more than one user-defined conversion from "B" to "const A" applies: -- function "B::operator A() const"
    // because f() accepts a A, and b can use operator A(), or A(co0nst B&), two ways to convert to A;
    // we have to tell compiler clearly
    A a1 = f(b.operator A());       // operator version
    A a2 = f(A(b));                 // constructor version
    // what if we use explicit operator
    // not work, because explicit cast b to a, still face how to create the A object, use A's constructor or B's operator

    // 2: build-in arithmetic type
    C c;
    // f2(c);               // error: more than one conversion function from "C" to "long double" applies

    long lg(0);
    C c2(lg);               // it works? but book said compiler will confuse about C::C(int) or C::C(double)

    // here are some tips about designing type converstion
    // first, define one way conversation, like if define A convert to B, then don't define B convert to A
    // avoid define conversations to build-in arithmetic type

    // overloaded function and conversation constructor
    mainip2(10);        // compile passed? MSVC ? "class E version"

    // overloaded function and user-defined type conversation
    // mainip3(10);        // error: more than one instance of overloaded function "mainip3" matches the argument list;
    // although there are an exact conversion from E(int 10), but if user defined available conversion is more than one,
    // there still be ambiguity
    return 0;
}