#include <memory>
#include <string>
#include <functional>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    // new and shared_ptr
    {
        shared_ptr<int> p1;
        shared_ptr<int> p2(new int(42));
        // shared_ptr<int> p3 = new int(42);     // explicit, must use direct initialization 
                                                 // error: no suitable constructor exists to convert from "int *" to shared_ptr<int>
        // cout << "base type double will not be inited " << *p1 << endl;
        cout << "base type int direct initialization " << *p2 << endl;  // uninitialized

        // error: no suitable constructor exists to convert from "int *" to shared_ptr<int>
        // auto clone = [](int p) -> shared_ptr<int>
        // {
        //     // return new int(p);  
        // }

        auto clone = [](int p) -> shared_ptr<int>
        {
            return shared_ptr<int>(new int(p));  // correct version
        };


        // another error version: make_shared is allocate new memory and initialize
        // auto clone = [](int p) -> shared_ptr<int>
        // {
        //     return make_shared<int>(new int(p));
        // };
        
        // here is the correct version
        auto clone2 = [](int p) -> shared_ptr<int>
        {   
            // allocate a shared ptr and init with 40
            return make_shared<int>(p);
        };

        auto pc1 = clone(10);
        auto pc2 = clone(20);
        *pc1 = 30;
        *pc2 = 30;
        // both work as expected
        cout << "use new with shared_ptr, the value is " << *pc1 << endl;
        cout << "use make_shared, the value is " << *pc2 << endl;
    }

    // mix use of normal pointer and smart pointer
    {
        int *q = new int(42);
        shared_ptr<int> p1(q);
        // shared_ptr<int> p2(q);
        // That won't cause a leak. 
        // It's actually much worse, since you have two unrelated shared pointers pointing to the same memory. 
        // Which means both will think they have ownership of the memory, and each will try to free it on their own.
        // it cause a runtime error when exit this scope, the two shared_ptr try to delete the same memory and they
        // don't know each other
        cout << "multi shared_ptr point to the same memory may cause runtime error" << endl;
    }

    {
        auto process = [](shared_ptr<int> ptr)
        {
            cout << "after passed by value, the current use count is " << ptr.use_count() << endl;
        };

        shared_ptr<int> p(new int(42));
        cout << "before passed to function, the use count is " << p.use_count() << endl;
        process(p);

        int *x(new int(1024));
        process(shared_ptr<int>(x));    // dangerous! the new created temporary shared_ptr will free this memory after function finish!
        int i = *x;                     // dangling pointer
        cout << i << endl;
    }

    // be careful with .get()
    {
        shared_ptr<int> p(new int(42));
        int *q = p.get();
        {
            shared_ptr<int>(q);
        }
        *q = 1;
        cout << "be careful with pointer that .get() returned, after shared_ptr release the memory, the pointer is dangling" << endl;
        cout << "the value is " << *p << endl;
        // summary: after using shared_ptr, don't give it back to normal pointer
    }

    // reset and unique
    {
        shared_ptr<int> p(new int());
        // p = new int(1024);      // error, explicit
        p.reset(new int(1024));     // now p is point to a new object

        shared_ptr<int> q(p);
        if(!p.unique())
            p.reset(new int(*q));
        *p += 10;
        cout << "p is " << *p << " q is " << *q << endl;
    }

    return 0;
}