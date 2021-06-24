#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    // destructor destory non static members
    // reverse order of constructor, invoke funtion, then destory memeber
    // and destructor don't have a destructor destroy list, so all depends on member's own destory method
    // we don't control the detail of destroy all member, it's automatic
    {
        class A
        {
        public:
            A()
            {
                cout << "A constructor" << endl;
            }
            ~A()
            {
                cout << "A destructor" << endl;
            }
        int *p;             // only destroy pointer itself, the int poined to will not be deleted;
        };

        class B
        {
        public:
            A a;
            B(): a()
            {
                cout << "B constructor" << endl;
            }
            ~B()
            {
                cout << "B destructor" << endl;
            }
        };
        B b;
        // A constructor
        // B constructor
        // B destructor
        // A destructor
    }

    // invoke timing of destructor
    {
        // leave scope
        // destroy an object, and it's member 
        // constianer destroied, it's element will be destoried
        // delete dynamic allocated memory
        // temp object
        class A
        {
        public:
            A()
            {
                cout << "A constructor" << endl;
            }
            ~A()
            {
                cout << "A destructor" << endl;
            }
        };

        A *p = new A();
        auto p2 = make_shared<A>();
        A item(*p);
        vector<A> vec;
        vec.push_back(*p2);
        delete p;               // A destructor
        // after leaving scope
        // item p2 vec call destructor
        // only dynamic allocated memory have to manualy delete
    }

    // synthesized destructor
    {
        class A
        {
        public:
            ~A(){ }     // equals the synthesized destructor
        }; 
    }
}