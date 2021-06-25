#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

class HasPtr{
    friend void swap(HasPtr&, HasPtr&);
public:
    HasPtr(const string &s = string());
    HasPtr(const HasPtr&);
    HasPtr& operator=(const HasPtr&);
    HasPtr& operator=(HasPtr);
    ~HasPtr();
    void Print();
private:
    int i;
    string* ps;
    size_t* pcount;
};

HasPtr::HasPtr(const string &s) : ps(new string(s)), i(0), pcount(new size_t(1)) {
    cout << "constructing " << *ps << " use count is " << *pcount << endl;
}

HasPtr::HasPtr(const HasPtr &ptr) : ps(ptr.ps), i(ptr.i), pcount(ptr.pcount) {
    ++(*pcount);
    cout << "copy constructing " << *ps << " use count is " << *pcount << endl;
}

HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
    ++(*rhs.pcount);
    if(--*pcount == 0){
        cout << "deleting " << *ps << " because assing new value, and use count have decreased to 0"<< endl;
        delete ps;
        delete pcount;
    }
    pcount = rhs.pcount;
    ps = rhs.ps;
    i = rhs.i;
    cout << "copy assigning " << *ps << " use count is " << *pcount << endl;
    return *this;
}

// copy and swap
HasPtr& HasPtr::operator=(HasPtr rhs){
    swap(*this, rhs);
    return *this;
}

HasPtr::~HasPtr()
{
    if(--*pcount == 0){
        cout << "use count of " << *ps << " have decreased to 0, free memory" << endl;
        delete ps;
        delete pcount;
    }
}

inline
void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    // why "using std::swap"?
    // because compiler first to find our version of swap, if don't find, then use std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
    swap(lhs.pcount, rhs.pcount);
}

int main()
{
    // why define our own swap?
    // because the general swap it:
    // A temp;
    // HasPtr temp = a;
    // a = b;
    // b = temp;
    // use copy constructor 1 time, copy assignment 2 times
    // but actually, we just need to swap some pointer

    // copy and swap, see the non reference version of operator =
    // HasPtr& HasPtr::operator=(HasPtr rhs){
    //  swap(*this, rhs);
    //  return *this;
    // }
    // because rhs is a copy of the origin one, so the swap operation won't affect the origin one
    // after swaping, the rhs's pointed memroy now is pointed by *this's pointer, and rhs will be destoried
    // after leaving function's scope
    return 0;
}