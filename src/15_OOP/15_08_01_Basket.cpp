#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <set>

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
    virtual Quote *clone() const &
    { return new Quote(*this); }
    virtual Quote* clone() &&
    { return new Quote(std::move(*this)); }
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

Quote::Quote(const Quote& q): bookNo(q.bookNo), price(q.price){}

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
    virtual Bulk_quote *clone() const &
    { return new Bulk_quote(*this); }
    virtual Bulk_quote* clone() &&
    { return new Bulk_quote(std::move(*this)); }
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

double print_total(ostream& os, const Quote& item, size_t n){
    double ret = item.net_price(n);
    os << "ISBN:" << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
    return ret;
}


class Basket{
public:
    void add_item(const shared_ptr<Quote>& sale)
    { items.insert(sale); }
    void add_item(const Quote& sale)
    { items.insert(shared_ptr<Quote>(sale.clone())); }
    void add_item(Quote&& sale)
    { items.insert(shared_ptr<Quote>(std::move(sale).clone())); }
    double total_receipt(ostream&) const;
private:
    static bool compare(const shared_ptr<Quote>& lhs, const shared_ptr<Quote>& rhs)
    { return lhs->isbn() < rhs->isbn(); }
    multiset<shared_ptr<Quote>, decltype(compare)*> items{compare};
};

double Basket::total_receipt(ostream& os) const{
    double sum = 0.0;
    for(auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter))
        sum += print_total(os, **iter, items.count(*iter));
    os << "Total Sale: " << sum << endl;
    return sum;
}

int main()
{
    Quote q("1", 20);
    Bulk_quote bq("2", 20, 20, 0.1);
    Basket bskq, bskbq;
    for(int i = 0; i < 50; ++i){
        bskq.add_item(q);
        bskbq.add_item(bq);
    }
    bskq.total_receipt(cout);
    bskbq.total_receipt(cout);
    return 0;
}