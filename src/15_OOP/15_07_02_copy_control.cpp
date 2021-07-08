#include <iostream>
#include <string>

using namespace std;

class B{
public:
    B();
    B(const B&) = delete;
};

class D: public B{
public:
    
};

class Quote{
public:
    Quote() = default;
    Quote(const Quote&) = default;
    Quote(Quote&&) = default;               // since we explitcly ask to define a copy constructor, we have to define a move constructor
    Quote& operator=(const Quote&) = default;
    Quote& operator=(Quote&&) = default;    // since we explitcly ask to define a copy assignment, we have to define a move assignment
    virtual ~Quote() = default;
};

int main()
{
    // just like normal synthesize rules
    // 01: if base class's default constructor, copy constuctor, copy assignment operato or destructor is deleted or inaccessible
    // compiler will not synthesize these for current derived class

    // 02: if base class's destructor is deleted or inaccessible, the synthesized default and copy constructor is deleted
    // because compiler is unable to destory the base part in dervied object (for compiler if can't destory it, then don't create it)

    // 03: compiler will not synthesize a deleted move constructor/assignment
    // if use = default ask compiler to create one (move constructor/assignment), 
    // but the base class's (move constructor/assignment) is deleted or inaccessible, then the function will be deleted, because can't move base part
    // same, if base destructor is deleted or inaccessible, then the derived move constructor is deleted

    D d;
    // D d2(d);                // error C2280: 'D::D(const D &)': attempting to reference a deleted function
    // D d3(std::move(d));     // error C2280: 'D::D(const D &)': attempting to reference a deleted function
    // why D d3(std::move(d)) don't work? because we defined a deleted copy constructor, so compiler will not synthesize move constructor
    // so use copy constructor, but copy constructor is deleted, so cause the error

    // move operation and inherition
    // sinece most base class will define a virtual destructor, so base class will not contain a synthesized move operation(see 15_07_01)
    // so if we want dervied classes to have move operation, we have to define our own, and as 13_06_02 mentioned, 
    // if class defined a move constructor or move assignment operator, the the sythesized cpoy constructor and copy assignment operator
    // will be defined as deleted, so we also have to define the copy operation aswell

    // summary: only no copy operations defined, then compiler will try to synthesized move operations.
    // otherwise your have to defined then by yourself.
    // I think it means that copy operations and move operations act alike, and compiler perfers copy operations
    return 0;
}