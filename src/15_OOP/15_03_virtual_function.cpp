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

//------------- 'override' keyword
struct B{
    virtual void f1(int i = 0) const{
        cout << "B's f1" << " default value is " << i << endl;
    }
    virtual void f2(){}
    void f3();
};

struct D1 : B{
    void f1(int i = 2) const override               // correct
    {
        cout << "D1's f1" << " default value is " << i << endl;
    }
    // void f2(int) const override;            // incorrect, same name, but parameter not match
    // void f3() override;                     // incorrect, f3 is not a virtual function
    // void f4() override;                     // incorrect, f4 don't exit in base class
};

struct D2 : B{
    void f1(int i = 3) const final
    {
        cout << "D2's f1" << " default value is " << i << endl;
    }
};

struct D3 : D2{
    void f2() override{};
    // void f1() override;         // can't overrider a final vitual function decalred in base class
};


int main()
{
    // must define all vitual functions!
    // because during compiling, complier don't know which version will be called, all version can be called in runtime
    {
        Quote base("0-201-82470-1", 50);
        print_total(cout, base, 10);
        Bulk_quote derived("0-201-82470-1", 50, 5, .19);
        print_total(cout, derived, 10);

        // dynamic bounding only available when using pointer or reference to call vitual functions
        base = derived;
        base.net_price(20);     // Quote version net_price
    }

    // virtual functions in derived classes
    {
        // keyword 'virtual' optional, sinece a function  declared as virtual, it will always be virtual in it's derived classes
        // derived virtual function: same parameters and return type
        // but if return type can be dynamic bound, like in base class return base*, in derived class return derived*
        // Base: virtual Base* func();
        // Derived: virtual Derived* func();
    }

    // final and override
    {
        // why use override?
        // because sometime we defined a very similar overrided function
        // but actually, there are some minor differces that don't successfully override the base one
        // so, add a 'override; at the end, tell compiler we defined a override function, and compiler will help us
        // to check the override correction
        // see struct B and D1

        // final is like the final access specifiers: it's the last vitual function
    }

    // default argument and vitual function
    {
        // will use the static type's default argument
        D1 d1;
        B* p = &d1;
        p->f1();    //called D1's vitual function, but uses B's defalut argument: D1's f1 default value is 0
    }

    // force to call specified version
    {
        Bulk_quote derived("0-201-82470-1", 50, 5, .19);
        Quote* baseP = &derived;
        cout << "force call base's virtual function, value is " << baseP->Quote::net_price(42);
    }

    return 0;
}