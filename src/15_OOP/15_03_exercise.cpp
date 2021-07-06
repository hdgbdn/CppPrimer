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
    virtual ostream& debug(ostream& os){
        os << "bookNo is " << bookNo << " price is " << price;
        return os;
    }
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
    virtual ostream& debug(ostream& os) override{
        Quote::debug(os) << " min_qty is " << min_qty << " discount is " << discount;
        return os;
    }
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

class base{
public:
    string name(){ return basename; }
    virtual void print(ostream &os)
    {
        cout << " base print ";
        os << basename;
    }

private:
    string basename;
};

class derived: public base{
public:
    void print(ostream &os)
    {
        
        // print(os); // infinity loop
        base::print(os);
        cout << " derived print ";
        os << " " << i;
    }
private:
    int i;
};

int main()
{
    // 15.11
    {
        Quote base("0-201-82470-1", 50);
        base.debug(cout) << endl;
        Bulk_quote derived("0-201-82470-1", 50, 5, .19);
        derived.debug(cout) << endl;
    }

    // 15.12
    // don't need, final contain's the meaning of override

    // 15.13
    // the print function in derived class should call the base's print function, or it will be infinity loop

    // 15.14
    {
        base bobj;
        base* bp1 = &bobj;
        base& br1 = bobj;
        derived dobj;
        base* bp2 = &dobj;
        base& br2 = dobj;

        bobj.print(cout);       // base::print(ostream &os)
        dobj.print(cout);       // derived::print(ostream &os)
        bp1->name();            // base::name()
        bp2->name();            // base::name()
        br1.print(cout);        // base::print(ostream &os)
        br2.print(cout);        // derived::print(ostream &os)
    }  

    return 0;
}