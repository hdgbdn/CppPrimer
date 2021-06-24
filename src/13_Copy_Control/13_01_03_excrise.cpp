#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

int main()
{
    // 13.9
    // release object memory, destroy non static data member
    // prefix of class name with a '~' and has no return value and takes no parameter
    
    // destory all non static member, the synthesized deconstructor is defined by complier when class don't define it's onw

    // 13.10
    // for StrBlob, the shader_ptr will be destroied, and decrease the reference count. if the count is zero, the vector pointed to will also be destroied
    // for StrBlobPtr, the weak_ptr is destroied, and the vector pointed by it will not be affected

    // 13.11
    class HasPtr{
        public:
            HasPtr(const string &s = string()): ps(new string(s)), i(0){}
            HasPtr(const HasPtr& ptr): ps(new string(*ptr.ps)), i(ptr.i){}
            ~HasPtr() { delete ps; }
        private:
            string* ps;
            int i;
        };
    
    // 13.12
    {
        class A
        {
        public:
            A(int v): val(v)
            {
                cout << "A constructor" << endl;
            }
            ~A()
            {
                cout << "A destructor" << endl;
            }
            int val;
        };
        auto fcn = [](const A *pa, A a)->bool
        {
            A item1(*pa), item2(a);
            return item1.val != item2.val;
        };
        const A* pa = new A(10);
        A a(20);
        fcn(pa, a);
        delete pa;
        // in fcn, A's destructor called 3 times,  a item1 item2, pa just a pointer, not object it self
    }

    // 13.13
    {
        struct X{
            X() {cout << "X()" << endl;}
            X(const X&) {cout << "X(const X&)" << endl;}
            X& operator=(const X& ){cout << "X& operator=(const X& )" << endl; return *this;}
            ~X() {cout << "~X()" << endl;}
        };

        cout << "non reference passed parameter --- start" << endl;
        auto f1 = [](X x){
            cout << "inside f1" << endl;
        };
        X x1;    // constructor
        f1(x1);  // copy constructor, and function finised, the value parameter will be destroied
        cout << "outside f1" << endl;
        cout << "non reference passed parameter --- end" << endl;
        
        cout << "reference passed parameter --- start" << endl;
        auto f2 = [](const X& x){
            cout << "inside f2" << endl;
        };
        X x2;    // constructor
        f2(x2);  // no constructor or deconstructor called
        cout << "outside f2" << endl;
        cout << "reference passed parameter --- end" << endl;
        
        cout << "dynamic allocate --- start" << endl;
        X* px = new X();            // X()
        auto f3 = [](X* px)-> X{
            cout << "inside f3" << endl;
            return X(*px);          // if we accpet the return value like X x3 = f3(px);, X(const x&), but if just f3(px), X(const x&)+~X()
        };
        f3(px);
        cout << "outside f3" << endl;
        cout << "dynamic allocate --- end" << endl;
        delete px;
    }
}