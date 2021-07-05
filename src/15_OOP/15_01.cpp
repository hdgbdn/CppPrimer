#include <iostream>
#include <string>

using namespace std;

class Quote{
public:
    Quote(string s = "0000", int p = 1): name(s), price(p) {}
    string isbn() const {return name; }
    // virtual function can be defined in different derived classes
    virtual double net_price(size_t n) const{
        cout << "The Quote version isbn()" << endl;
        return n * price;
    }
private:
    string name;
    int price;
};

class Bulk_quote: public Quote{
public:
	// override virtual function
    double net_price(size_t n) const override{
        cout << "The Bulk_quote version isbn()" << endl;
        return 0;
    }
};

double print_total(ostream& os, const Quote& item, size_t n){
    double ret = item.net_price(n);
    os << "ISBN:" << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
    return ret;
}

int main()
{
    // inheritance

    // virtual function
    // same name, but different function in different derived classes
    Quote q("Quote", 999);
    Bulk_quote bq;

    // dynamic binding
    // only pointer and reference!!!!
    print_total(cout, q, 100);
    print_total(cout, bq, 100);

    return 0;
}