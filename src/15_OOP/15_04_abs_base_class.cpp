#include <iostream>
#include <string>

using namespace std;

class Quote{
public:
    Quote() = default;
    Quote(const string& book, double sales_price):bookNo(book), price(sales_price) {}
    string isbn() const { return bookNo; }
    virtual double net_price(size_t n) const{
        cout << "Quote version net_price" << endl;
        return n * price;
    }
    virtual void no_need_to_override() { cout << "Quote class: no need to override this function" << endl; }
private:
    string bookNo;
protected:
    double price;
};

class Disc_quote : public Quote{
public:
    Disc_quote() = default;
    Disc_quote(const string& book, double price, size_t qty, double dis):
        Quote(book, price), quantity(qty), discount(dis) {}
    double net_price(size_t) const = 0;         // optional 'virtual' keyword

protected:
    size_t quantity = 0;
    double discount = 0.0;
};

class Bulk_quote : public Disc_quote
{
public:
    Bulk_quote() = default;
    Bulk_quote(const string &book, double price, size_t qty, double dis) : Disc_quote(book, price, qty, dis) {}
    virtual double net_price(size_t) const override;
};

double Bulk_quote::net_price(size_t cnt) const
{
    cout << "Bulk version net_price" << endl;
    if (cnt >= quantity)
        return cnt * price * (1 - discount);
    else
        return cnt * price;
}

int main()
{
    // an abstract base class means we don't want to create any objects from this class
    // it cantains abstract members that only can be derived
    // compiler will not allow creating objects from abstract base class
    // a abstract base class

    // pure virtual function
    // can only be decalred
    // a class has (or derived but not overload) a pure vitual function
    // is abstract base class
    // Disc_quote dc;       // object of abstract class type "Disc_quote" is not allowed: -- function "Disc_quote::net_price" is a pure virtual function

    // although bulk_quote don't declar it's own member, it still need to construct it's derived members, by calling it's direct base's constructor
    return 0;
}