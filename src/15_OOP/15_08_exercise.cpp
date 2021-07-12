#include <iostream>
#include <string>
#include <vector>
#include <memory>

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
        return n * price;
    }
    virtual void no_need_to_override() { cout << "Quote class: no need to override this function" << endl; }
private:
    string bookNo;
protected:
    double price;
};

Quote::Quote(const string& book, double sales_price): bookNo(book), price(sales_price){
}

Quote::Quote(const Quote& q): bookNo(q.bookNo), price(q.price){
}

Quote::Quote(Quote&& q): bookNo(std::move(q.bookNo)), price(std::move(q.price)){
}

Quote& Quote::operator=(const Quote& rhs){
    bookNo = rhs.bookNo;
    price = rhs.price;
    return *this;
}

Quote& Quote::operator=(Quote&& rhs){
    bookNo = std::move(rhs.bookNo);
    price = std::move(rhs.price);
    return *this;
}

Quote::~Quote(){
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
}

Disc_quote::Disc_quote(const Disc_quote& dq): Quote(dq), quantity(dq.quantity), discount(dq.discount){
}

Disc_quote::Disc_quote(Disc_quote&& rhs): Quote(std::move(rhs)), quantity(std::move(rhs.quantity)), discount(std::move(rhs.discount)){
}

Disc_quote& Disc_quote::operator=(const Disc_quote& rhs){
    Quote::operator=(rhs);
    quantity = rhs.quantity;
    discount = rhs.discount;
    return *this;
}

Disc_quote& Disc_quote::operator=(Disc_quote&& rhs){
    Quote::operator=(std::move(rhs));
    quantity = std::move(rhs.quantity);
    discount = std::move(rhs.discount);
    return *this;
}

Disc_quote::~Disc_quote(){
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
}

Bulk_quote::Bulk_quote(const Bulk_quote& rhs): Disc_quote(rhs){
}

Bulk_quote::Bulk_quote(Bulk_quote&& rhs): Disc_quote(std::move(rhs)){
}

Bulk_quote& Bulk_quote::operator=(const Bulk_quote& rhs){
    Disc_quote::operator=(rhs);
    return *this;
}

Bulk_quote& Bulk_quote::operator=(Bulk_quote&& rhs){
    Disc_quote::operator=(std::move(rhs));
    return *this;
}

Bulk_quote::~Bulk_quote(){
}

double Bulk_quote::net_price(size_t cnt) const
{
    if (cnt >= quantity)
        return cnt * price * (1 - discount);
    else
        return cnt * price;
}

int main()
{
    vector<shared_ptr<Quote>> basket;
    Quote q("1", 20);
    Bulk_quote bq("2", 20, 10, 0.1);
    basket.push_back(make_shared<Quote>(q));
    cout << "Quote pointer Quote object: " << basket.back()->net_price(40) << endl;
    basket.push_back(make_shared<Bulk_quote>(bq));
    cout << "Bulk_quote pointer Bulk_quote object: " << basket.back()->net_price(40) << endl;
    
    // 15.29
    // the result is different
    basket.push_back(make_shared<Quote>(bq));
    cout << "Quote pointer Bulk_quote object: " << basket.back()->net_price(40) << endl;
    // I think the make_shared template is Quote, so it new a Quote object, and the derived part is been cut off
    
    return 0;
}