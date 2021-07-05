#include <iostream>
#include <string>

using namespace std;

class Quote {
public:
    Quote() = default;
    Quote(const string& book, double sales_price): bookNo(book), price(sales_price) {}
    string isbn() const { return bookNo; }
    virtual double net_price(size_t n) const { return n * price; }
    virtual ~Quote() = default;
private:
    string bookNo;
protected:
    double price = 0.0;
};

int main()
{
    // the destructor is virtual
    // and the protected access specifiers

    // base class's member function, if want their derived classes keep it, then non virtual
    // if want derived classes to override it, then declar as virtual
    // vitual function is being dynamic bound when call a vitrual function by reference or pointer
    // any non static function excpet constructor can be declared as vitrual function

    // access specifiers: public protected private
    // protected member: derived classes can access, but other users can't access
    // and derived classes can't access base class's private member
    return 0;
}