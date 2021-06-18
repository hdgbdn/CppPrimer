#include <memory>
#include <string>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

int *Foo(int i)
{
    return new int(i);
};

int main()
{
    // use new to allocate and initialize objects
    {
        int *pi = new int;  // uninitialized for basic data types
        string *ps = new string; // class objects will use default constructor
    }

    {
        int *pi = new int(1024);
        string *ps = new string(10, '9');   // direct initialization
        vector<int> *pv = new vector<int> {1,2,3,4}; // use initializer_list
    }

    {
        string *ps1 = new string;   // default initialization
        string *ps2 = new string(); // value initialization, for class type, it just called default initialization, so it is same as default
        int *pi1 = new int;         // undefined
        int *pi2 = new int();       // value initialization
        cout << *pi1 << endl;       // -842150451
        cout << *pi2 << endl;       // 0
    }

    {
        auto autoP1 = new auto("string");
        try
        {
            //auto autoP2 = new auto {"a", "b", "c"}; //error C2076: a brace-enclosed initializer list cannot be used in a new-expression whose type contains 'auto'
        }
        catch (std::exception err)
        {
            std::cerr << err.what() << std::endl;
        }
    }

    // dynamic allcated const object
    {
        const int *pci1 = new const int(1024);      // for basic types: const object must be initialized
        //const int *pci2 = new const int;          // error C2737: 'const int': const object must be initialized
        const string *pcs1 = new const string;      // for class type object that defined default constructor, implicit construction will be called
        const string *pcs2 = new const string();    // value initialization, same as default initialization
    }

    // out of memory
    {
        // TODO
    }

    // delete
    {
        int i, *pi1 = &i, *pi2 = nullptr;
        double *pd = new double(33), *pd2 = pd;
        //delete i;             // error C2541: 'delete': cannot delete objects that are not pointers
        //delete pi1;           // undefined, runtime error, i is not dynamic allocated          
        delete pd;              // works as expected
        //delete pd2;           // undefined, runtime error, point to a deleted pointer

        const int *pci = new const int(1024);
        //*pci = 2;             // expression must be a modifiable lvalue
        delete pci;             // const cannot be modified, but can be deleted
    }

    // why need delete
    {
        int *p = Foo(1024);
        // delete p;               // 1. forgot to delete! if don't delete, there will be a memory leak!
        // Foo(*p)                 // 2. use a deleted pointer
        // delete p;               // 3. delete twice 
    }

    // dangling pointer
    {
        int *p(new int(42));
        int *q = p;
        delete p;   // but q is still point to the memory that is already freed
        p = nullptr;
        cout << "q's point after deleting p is " << *q << endl;
    }
}