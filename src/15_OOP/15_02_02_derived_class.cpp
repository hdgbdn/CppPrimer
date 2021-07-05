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
            return cnt * price * (1 -discount);
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

//sssssssssssssssssssssssssssssssssssssssstatic memberrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
class Base{
public:
    static void statmem(){ cout << "Base static function: statmem" << endl;}
};



class Derived final : public Base {
public:
    void f(const Derived&);
};

/*
class Derived2 : Derived{
    a 'final' class type cannot be used as a base class
};
*/

// only one static member, but can be called in different forms
void Derived::f(const Derived& derived_obj){
    Base::statmem();            // by base class
    Derived::statmem();         // by derived class
    derived_obj.statmem();      // by derived obj 
    statmem();                  // by this pointer
}

int main()
{
    // the derived class from Quote is above
    // "bookNo" "price" "isbn" will be derived, and add two new members,
    // also override the origin "net_price" member function
    Bulk_quote bq;
    // virtual function is not forced to be overrideed
    bq.no_need_to_override();

    // type conversation
    // the base part and dervide part's data in memory may not be continuous
    // but logically is continuous

    // since dervided object has a full base class's member, so we can use dervide object as base object
    // or bind base class's pointer or reference to a derided object
    // it is called "derived-to-base" conversation
    {
        Quote item;
        Bulk_quote bulk;
        Quote *p = &item;
        p = &bulk;
        Quote &r = bulk;
    }

    // important!!!!!!!!!!!!!!!!!!!!!!
    // if a derived class want to interact with it's base class, it has to use the interface base class provided,
    // it's not recommand to directly set protected and public members of base class in derived class's constructor

    // about static member
    // static member will be unique in all base and derived classes
    Derived d_obj;
    d_obj.f(d_obj);

    // declaraion
    // shouldn't contain class derivation list
    // because complier just want to konw the name, not the detail
    // class Bulk_quote : public Quote;     // error
    // class Bulk_quote;                    // correct

    // the class used as base class shoule be well defined;
    // two reasons: first, derived class need to konw the detail of base class
    // second, class can't derive itself

    // direct base and indirect base
    // class Base { /* ... */ };
    // class D1: public Base { /* ... */ };
    // class D2: public D2 { /* ... */ };
    // Base is the direct base of D1, the indirect base of D2

    // prevent Derive
    // see the "Derived" class above
    return 0;
}