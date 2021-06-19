#include <memory>
#include <string>
#include <functional>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    auto process = [](shared_ptr<int> ptr)
    {
        cout << "after passed by value, the current use count in function scope is " << ptr.use_count() << endl;
    };

    // 12.10 correct, shared_ptr is passed as expect
    {
        shared_ptr<int> p(new int(42));
        cout << "before passed by value, use count is " << p.use_count() << endl;
        process(shared_ptr<int>(p));
        cout << "after function, use count is " << p.use_count() << endl;
    }

    // 12.11 wrong, the new shared_ptr is not created from the origin one
    {
        shared_ptr<int> p(new int(42));
        process(shared_ptr<int>(p.get()));
        cout << "after function, use count is " << p.use_count() << endl;
        return 0;
    }

    // 12.12
    {
        auto p = new int();
        auto sp = make_shared<int>();
        process(sp);    // correct
        //process(new int ()); // error, explicit
        //process(p);     // error, explicit
        //process(shared_ptr<int>(p)) // error, after function, p will be destoried by the passed value
    }

    // 12.13
    {
        auto sp = make_shared<int>();
        auto p = sp.get();
        //delete p; // sp become a dangling pointer
    }

}