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

class My_bulk : public Disc_quote{
public:
    My_bulk() = default;
    My_bulk(const string& book, double sales_price, size_t qty, double disc):
    Disc_quote(book, sales_price, qty, disc) {}
    // override the Quote's version
    double net_price(size_t cnt) const override{
        if (cnt <= quantity)
            return cnt * price * (1 - discount);
        else
            return quantity * price * (1 - discount) + (cnt - quantity) * price;
    };
};

double print_total(ostream& os, const Quote& item, size_t n){
    double ret = item.net_price(n);
    os << "ISBN:" << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
    return ret;
}

int main()
{
    // 15.15
    // see above

    // 15.16
    My_bulk my_bulk("0003", 10, 20, 0.1);
    print_total(cout, my_bulk, 30);

    // 15.16
    // Disc_quote dc;          // 'Disc_quote': cannot instantiate abstract class

    return 0;
}