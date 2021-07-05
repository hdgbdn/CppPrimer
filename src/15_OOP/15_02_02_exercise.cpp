#include <iostream>
#include <string>

using namespace std;

class Quote{
public:
    Quote() = default;
    Quote(const string& book, double sales_price):bookNo(book), price(sales_price) {}
    string isbn() const { return bookNo; }
    virtual double net_price(size_t n) const { return n * price; }
    virtual void no_need_to_override() { cout << "Quote class: no need to override this function" << endl; }
private:
    string bookNo;
protected:
    double price;
};

class Bulk_quote : public Quote{
public:
    Bulk_quote() = default;
    // add two parameters
    Bulk_quote(const string& book, double sales_price, size_t qty, double disc) : 
    // the base part's construction give back to base class
    Quote(book, sales_price), min_qty(qty), discount(disc) {}
    // override the Quote's version
    double net_price(size_t cnt) const override{
        if (cnt >= min_qty)
            return cnt * price * (1 - discount);
        else
            return cnt * price;
    };
private:
    // added two private member
    size_t min_qty;
    double discount = 0.0;
};

class My_bulk : public Quote{
public:
    My_bulk() = default;
    // add two parameters
    My_bulk(const string& book, double sales_price, size_t qty, double disc) : 
    // the base part's construction give back to base class
    Quote(book, sales_price), min_qty(qty), discount(disc) {}
    // override the Quote's version
    double net_price(size_t cnt) const override{
        if (cnt <= min_qty)
            return cnt * price * (1 - discount);
        else
            return min_qty * price * (1 - discount) + (cnt - min_qty) * price;
    };
private:
    // added two private member
    size_t min_qty;
    double discount = 0.0;
};

double print_total(ostream& os, const Quote& item, size_t n){
    double ret = item.net_price(n);
    os << "ISBN:" << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
    return ret;
}

int main()
{
    // 15.4
    // class Derived : public Derived { ... };  // Incorrect, con't derived from self
    // class Derived : private Base { ... };    // Incorrect, it's defination, not declaration
    // class Derived : public Base;             // Incorrect, should'n add derivation list

    // 15.5
    Quote q("0001", 10);
    Bulk_quote bulk("0002", 10, 20, 0.1);
    print_total(cout, q, 30);
    print_total(cout, bulk, 30);

    My_bulk my_bulk("0003", 10, 20, 0.1);
    print_total(cout, my_bulk, 30);
    return 0;
}