#include <iostream>
#include <string>

using namespace std;

class A{
public:
    A& operator+(const A&) {cout << "member function version" << endl; return *this; }
};

A operator+(const A& lhs, const A& rhs)
{
    cout << "non member function version" << endl;
    return A();
}

int main()
{
    // 1. parameters, unary operator and binary operator
    // a operator function as an memberfunction, it's left parameter will be implicit
    A a1, a2;
    A a3;
    a3 = a1 + a2;               // member function version, but if don't define the member version, it will use the non member version
    a3 = operator+(a1, a2);     // non member function version
    a3 = a1.operator+(a2);      // member function version

    // 2. generally, we shouldn't override the ',' '&' '&&' and '||'
    // for ',' and '&', it's have been widely used
    // '&&' and '||', the overrided version will not have logically shortcut

    // 3. member or non-member?
    // '=' '[]' '()' '->' should be member, because it use the object's data member
    // '+=' '-=' ... can be member, but also can be non-member
    // '++' '--' '*', changes objects' themselves, should be member
    // lhs and rhs can swap: '+' '-' '==' '!=' should be non-member function


    // operator as member functio, the lhs should be the class type
    // because it's called like lhs.operator+(rhs),
    string s = "world";
    string t = s + '!';     // '+' as a member function
    string u = "hi" + s;    // if '+' is string's member function, then it will be error because const char don't have a + member funtion
    // so the '+' above is a non-member functions
}