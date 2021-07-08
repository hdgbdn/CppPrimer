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

int main()
{
    // 15.25
    // because we defined our user constructor, so the complier will not synthesize default constructor for us,
    // then we have to use our user defined version constructor
    return 0;
}