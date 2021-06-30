#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

class Foo{
public:
    Foo& operator=(const Foo&) &;       // only can be called by lvalue
    Foo sorted() const &;
    Foo sorted() &&;
private:
    vector<int> data;
};

Foo& Foo::operator=(const Foo& rhs) &{
    return *this;
}

// although return a reference of a local varable is incorrect, it just showcase it's return value is a lvalue;
Foo &retFoo(){
    return Foo();
}

Foo retVal(){
    return Foo();
}

//----------------
Foo Foo::sorted() &&{
    cout << "sorted: rvalue version" << endl;
    sort(data.begin(), data.end());
    return *this;
}

// const or lvalue, we can't sort on the origin memory
//  you cannot assign to a variable that is const
Foo Foo::sorted() const &{
    cout << "sorted: const or lvalue version" << endl;
    Foo ret(*this);
    sort(ret.data.begin(), ret.data.end());
    return ret;
}

int main(){
    // const X& and X&& match rule:
    // any objects which can be cast to X, matches const X&
    
    Foo i, j;
    retFoo() = i;       // correct, assign to rvalue
    // retVal() = j;       // error, & consist just can be used in lvalue

    // const and & and && order
    // Foo someMember() & const: error, const must in left
    // Foo someMember() const &: correct

    // reference qualifier can be used in override
    // we want sorted to return a sorted copy of origin object
    // so for rvalue version, it's ok to sort itself
    // but for lvalue or const version, we need make a copy and sort the copy
    i.sorted();             // sorted: const or lvalue version
    std::move(i).sorted();  // sorted: rvalue version
    return 0;
}