#include <iostream>
#include <string>

using namespace std;

class Quote{
public:
    Quote() = default;
    Quote(const string& book, double sales_price):bookNo(book), price(sales_price) {}
    string isbn() const { return bookNo; }
    virtual double net_price(size_t n) const { return n * price; }
protected:
    string bookNo;
private:
    double price;
};

double print_total(ostream& os, const Quote& item, size_t n){
    double ret = item.net_price(n);
    os << "ISBN:" << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
    return ret;
}

int main()
{
    // 15.1
    // a virtual function is function that can be overrided by derived classes
    // can be dynamic bound if called by reference or pointer

    // 15.2
    // protected members can be accessed by derived classes

    // 15.3
    Quote q("100-101001010-1", 87.99);
    print_total(cout, q, 100);
    return 0;
}