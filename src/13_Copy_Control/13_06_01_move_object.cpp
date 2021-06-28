#include <iostream>
#include <string>
#include <memory>

using namespace std;

int main()
{
    // in new standrad, container can save non-copiable element, when they can be moved;
    // container string and shared_ptr support copy and move
    // io and unique_ptr can move but can't copied
    
    // rvalue reference

    // a rvalue represents it's value
    // a lvalue represents it's type & name
    {
        int i = 42;
        int &r = i;
        // int &&r = i;             // an rvalue reference cannot be bound to an lvalue
        // int &r2 = i * 42;        // initial value of reference to non-const must be an lvalue, i * 42 is a rvalue
        const int &r3 = i * 42;     // const reference can be bound to a lvalue
        int &&rr2 = i * 42;         // bond rvalue to a rvalue 
    }

    // varables are lvalue
    // rvalue is temporate

    // std::move
    {
        int &&rr1 = 42;
        // cast an lvalue to rvalue
        int &&rr3 = std::move(rr1);
    }
}