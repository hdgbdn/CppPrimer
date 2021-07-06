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

class Bulk_quote : public Quote{
public:
    Bulk_quote() = default;
    // add two parameters
    Bulk_quote(const string& book, double sales_price, size_t qty, double disc) : 
    // the base part's construction give back to base class
    Quote(book, sales_price), min_qty(qty), discount(disc) {}
    // override the Quote's version
    double net_price(size_t cnt) const override{
        cout << "Bulk version net_price" << endl;
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

double print_total(ostream& os, const Quote& item, size_t n){
    double ret = item.net_price(n);
    os << "ISBN:" << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
    return ret;
}


int main()
{
    // dynamic bounding: we can bind base type's pointer or reference to dervived objects

    // static type and dynamic type
    // static type is konwn in compiling, but dynamic type is konwn until running
    {  
        // p's static type is Quote*, it's dynamic type is unkonw until program running, in this case, it's a Bulk_quote
        // only pointer and reference have this property, other types' dynamic typekeep same with static type 
        Quote* p;
        p = new Bulk_quote();
        p->net_price(10);
        delete p;
    }

    // since a base class object is just a part of it's derived class, so we can't convert a base object into a derived one
    // because it may enable access of non exiting derived's part
    {
        Quote base;
        // Bulk_quote* bulkP = &base;      // incorrect: a value of type "Quote *" cannot be used to initialize an entity of type "Bulk_quote *"
        // Bulk_quote& bulkRef = base;     // incorrect:a reference of type "Bulk_quote &" (not const-qualified) cannot be initialized with a value of type "Quote"

        // event a base pointer/reference is bound to a dervied object, it still can't convert to dervied type
        // because in compiling, compiler don't know it's dynamic type is dervide
        Bulk_quote bulk;
        Quote *itemP = &bulk;
        // Bulk_quote *bulkP = itemP;      // a value of type "Quote *" cannot be used to initialize an entity of type "Bulk_quote *"
        // but we can cast!
        Bulk_quote *d_bulkP = dynamic_cast<Bulk_quote *>(itemP);    // dynamic cast, the safety check will run in runtime
        cout << "dynamic_cast result is " << d_bulkP->net_price(1) << endl;
        // or force cast
        Bulk_quote *s_bulkP = static_cast<Bulk_quote *>(itemP);     // static cast, the safety check will be ignored
        cout << "static_cast result is " << s_bulkP->net_price(1) << endl;
        // delete itemP;    // error, only the pointer points to a heap memory can be deleted!!!!!
    }

    // there is no conversation between base object and dervied object
    {
        Bulk_quote bulk;
        Quote item(bulk);       // called function Quote(const Quote&): just us bulk's base part to construct a new base object(item);
        item = bulk;            //called function Quote& Quote::operator=(const Quote&): just copy the base part;
        // the derived part is *sliced down*
    }



    return 0;
}