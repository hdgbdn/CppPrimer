#include <iostream>
#include <string>

using namespace std;

class Base{

};

class D: public Base{
public:
    D(const D& d): Base(d){};           // copy base part
    D(D&& d): Base(std::move(d)){};     // move base part
    D& operator=(const D&);
    ~D() {};
};

D& D::operator=(const D& rhs){
    Base::operator=(rhs);       // although it's a synthesized version, we still can use it
    return *this;
}

int main()
{
    // in construction, we have to control base part's construction
    // but in destruction, we don't need to control base part's destruction

    // copy & move constructor in derived class
    // in class D above, we use Base(d), a derived object to copy construct a base object
    // why it works? because B's copy constructor B::B(const B&), the derived objecet is bound to const B&
    // what if we don't mannualy construct base part? the base part will use default construction
    // so if like this: D(const D& d): {};, it will be starange because the base part is default, and the derived part is copied
    // so we have to explicitly use base's constructor

    // derived assignment operator
    // have to explicitly call base's assignment operator
    // see D& D::operator=(const D& rhs) above

    // destructor
    // unlike the constructor and assignment operations, the destruction is implicitly called
    // so we just control the derived part

    // calling virtual functions in constructor and destructor
    // during constructing base part, the derived part is un constructed, and so in destructing base part, the dervrived part is destroied
    // so if constructor or destructor call some virtual function, use the constructor or destructor's class's version's virtual function
    return 0;
}