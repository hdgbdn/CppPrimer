#include <memory>
#include <string>
#include <functional>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    // unique_ptr
    {   
        // only can be initialized by new returned pointer 
        unique_ptr<double> p1;
        unique_ptr<int> p2(new int(42));
    }

    // why unique
    {
        unique_ptr<string> p1(new string("a"));
        // copy construction and assign are deleted
        // unique_ptr<string> p2(p1);                // copy construction is deleted
        // unique_ptr<string> p3;
        // p3 = p1;                                  // assign is deleted

        // release return the control of memory; reset release the origin memory and accpet a new pointer
        unique_ptr<string> p2(p1.release());
        // cout << "after release to p2, p1's value is" << *p1 << endl; // P1 is dangling
        cout << "after release to p2, p2's value is " << *p2 << endl;
        unique_ptr<string> p3(new string("b"));
        p2.reset(p3.release());
        cout << "after p3 release to p2, p2's value is " << *p2 << endl;

        // p2.release();
        auto p = p2.release();
        delete p;       // remember to delete p, because p is a normal pointer
    }

    // pass and return unique_ptr
    {
        // two conditions that unique_ptr can be copied
        // 1. return by a function
        auto clone = [](int p)->unique_ptr<int>
        {
            return unique_ptr<int>(new int(p));
        };
        
        // 2. or return a copy of local variable
        auto clone2 = [](int p)->unique_ptr<int>
        {
            unique_ptr<int> ret(new int(p));
            return ret;
        };

        // both the variable will be destory
    }

    // pass deleter
    {
        // unique_ptr<connection, decltype(end_connnection)*> p(&c, end_connection);
        // decltype is get the type of function `end_connection`
    }
}