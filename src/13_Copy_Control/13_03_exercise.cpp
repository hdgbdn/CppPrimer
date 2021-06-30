#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

class HasPtr{
    friend void swap(HasPtr&, HasPtr&);
public:
    HasPtr(const string &s = string());
    HasPtr(const HasPtr&);
    //HasPtr& operator=(const HasPtr&);
    HasPtr& operator=(HasPtr);
    bool operator<(const HasPtr &rhs) const;
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

/*
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
*/

HasPtr& HasPtr::operator=(HasPtr rhs){
    cout << "copy assigning from " << *rhs.ps << " to " << *ps << " use count is " << *pcount << endl;
    swap(*this, rhs);
    return *this;
}


bool HasPtr::operator<(const HasPtr &rhs) const{
    return *ps < *rhs.ps;
};

HasPtr::~HasPtr()
{
    if(--*pcount == 0){
        cout << "use count of " << *ps << " have decreased to 0, free memory" << endl;
        delete ps;
        delete pcount;
    }
}

void HasPtr::Print(){
    cout << "string is " << *ps << " use count is " << *pcount << endl;
}

inline
void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    cout << "swaping " << *lhs.ps << " " << *rhs.ps << endl;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
    swap(lhs.pcount, rhs.pcount);
}

int main()
{
    // 13.29
    // the swap inside swap(HasPtr &lhs, HasPtr &rhs) is the std version

    // 13.30
    // question, which version will be called
    // HasPtr& operator=(const HasPtr&);
    // HasPtr& operator=(HasPtr);
    // answer: more than one operator "=" matches these operands, so only can define one
    cout << "--------------------------13.30" << endl;
    HasPtr hello("hello");
    HasPtr hi("hi");
    swap(hello, hi);
    swap(hello, hi);
    hi = hello;     // the copy and swap version works well, hi is released

    // 13.31
    cout << "--------------------------13.31" << endl;
    vector<HasPtr> vec;
    HasPtr longStr("hello");
    HasPtr shortStr("hi");
    vec.push_back(shortStr);
    vec.push_back(longStr);
    cout << "before sorting " << endl;
    for(auto p : vec) p.Print();
    sort(vec.begin(), vec.end());       // sort uses the HasPtr::swap function
    cout << "after sorting " << endl;
    for(auto p : vec) p.Print();

    cout << "--------------------------leaving scope" << endl;

    // 13.32
    // No, build-in types are swapped efficiently using library swap
    return 0;
}