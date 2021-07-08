#include <iostream>
#include <string>

using namespace std;

class Quote{
public:
    Quote() = default;
    Quote(const string&, double);
    Quote(const Quote&);
    Quote(Quote&&);
    Quote& operator=(const Quote&);
    Quote& operator=(Quote&&);
    virtual ~Quote();
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

Quote::Quote(const string& book, double sales_price): bookNo(book), price(sales_price){
    cout << "Quote::Quote(const string&, double)" << endl;
}

Quote::Quote(const Quote& q): bookNo(q.bookNo), price(q.price){
    cout << "Quote::Quote(const Quote&)" << endl;
}

Quote::Quote(Quote&& q): bookNo(std::move(q.bookNo)), price(std::move(q.price)){
    cout << "Quote::Quote(const Quote&)" << endl;
}

Quote& Quote::operator=(const Quote& rhs){
    cout << "Quote& Quote::operator=(const Quote&)" << endl;
    bookNo = rhs.bookNo;
    price = rhs.price;
    return *this;
}

Quote& Quote::operator=(Quote&& rhs){
    cout << "Quote& Quote::operator=(Quote&&)" << endl;
    bookNo = std::move(rhs.bookNo);
    price = std::move(rhs.price);
    return *this;
}

Quote::~Quote(){
    cout << "Quote::~Quote()" << endl;
}

class Disc_quote : public Quote{
public:
    Disc_quote() = default;
    Disc_quote(const string&, double, size_t, double);
    Disc_quote(const Disc_quote&);
    Disc_quote(Disc_quote&&);
    Disc_quote& operator=(const Disc_quote&);
    Disc_quote& operator=(Disc_quote&&);
    virtual ~Disc_quote() override;
    double net_price(size_t) const = 0;         // optional 'virtual' keyword

protected:
    size_t quantity = 0;
    double discount = 0.0;
};

Disc_quote::Disc_quote(const string& book, double price, size_t qty, double dis):
        Quote(book, price), quantity(qty), discount(dis){
            cout << "Disc_quote::Disc_quote(const string&, double, size_t, double)" << endl;
}

Disc_quote::Disc_quote(const Disc_quote& dq): Quote(dq), quantity(dq.quantity), discount(dq.discount){
    cout << "Disc_quote::~Disc_quote(const Disc_quote&)" << endl;
}

Disc_quote::Disc_quote(Disc_quote&& rhs): Quote(std::move(rhs)), quantity(std::move(rhs.quantity)), discount(std::move(rhs.discount)){
    cout << "Disc_quote::Disc_quote(Disc_quote&&)" << endl;
}

Disc_quote& Disc_quote::operator=(const Disc_quote& rhs){
    cout << "Disc_quote& Disc_quote::operator=(const Disc_quote&)" << endl;
    Quote::operator=(rhs);
    quantity = rhs.quantity;
    discount = rhs.discount;
    return *this;
}

Disc_quote& Disc_quote::operator=(Disc_quote&& rhs){
    cout << "Disc_quote& Disc_quote::operator=(Disc_quote&&)" << endl;
    Quote::operator=(std::move(rhs));
    quantity = std::move(rhs.quantity);
    discount = std::move(rhs.discount);
    return *this;
}

Disc_quote::~Disc_quote(){
    cout << "Disc_quote::~Disc_quote()" << endl;
}

class Bulk_quote : public Disc_quote
{
public:
    Bulk_quote() = default;
    Bulk_quote(const string &, double , size_t , double);
    Bulk_quote(const Bulk_quote&);
    Bulk_quote(Bulk_quote&&);
    Bulk_quote& operator=(const Bulk_quote&);
    Bulk_quote& operator=(Bulk_quote&&);
    ~Bulk_quote();
    virtual double net_price(size_t) const override;
};

Bulk_quote::Bulk_quote(const string &book, double price, size_t qty, double dis): Disc_quote(book, price, qty, dis){
    cout << "Bulk_quote::Bulk_quote(const string&, double, size_t, double)";
}

Bulk_quote::Bulk_quote(const Bulk_quote& rhs): Disc_quote(rhs){
    cout << "Bulk_quote::Bulk_quote(const Bulk_quote&)" << endl;
}

Bulk_quote::Bulk_quote(Bulk_quote&& rhs): Disc_quote(std::move(rhs)){
    cout << "Bulk_quote::Bulk_quote(Bulk_quote&&)" << endl;
}

Bulk_quote& Bulk_quote::operator=(const Bulk_quote& rhs){
    cout << "Bulk_quote& Bulk_quote::operator=(const Bulk_quote&)" << endl;
    Disc_quote::operator=(rhs);
    return *this;
}

Bulk_quote& Bulk_quote::operator=(Bulk_quote&& rhs){
    cout << "Bulk_quote& Bulk_quote::operator=(Bulk_quote&&)" << endl;
    Disc_quote::operator=(std::move(rhs));
    return *this;
}

Bulk_quote::~Bulk_quote(){
    cout << "Bulk_quote::~Bulk_quote()" << endl;
}

double Bulk_quote::net_price(size_t cnt) const
{
    cout << "Bulk version net_price" << endl;
    if (cnt >= quantity)
        return cnt * price * (1 - discount);
    else
        return cnt * price;
}

Bulk_quote func(){
    return Bulk_quote();
}

int main()
{
    Bulk_quote bq;
    cout << "using move construction" << endl;
    Bulk_quote bq2(std::move(bq));
    cout << "using move assignment" << endl;
    bq2 = func();
    cout << "Exiting" << endl;
    // if want to use move operation, should use std::move
    // see the dervide classes's move operations above
    return 0;
}