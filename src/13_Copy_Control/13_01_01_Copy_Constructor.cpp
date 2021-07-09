#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    // copy constructor
    {
        class Foo{
        public:
            Foo() {cout << "default constructor" << endl;}            // default constructor
            Foo(const Foo&) {cout << "copy constructor" << endl; }    // copy constructor, parameter should be const &
        };
        Foo f1;             // default constructor
        Foo f2 = Foo();     // default constructor
        Foo f3(f1);         // copy constructor
    }

    // synthesized copy constructor
    {
        // compiler will make a copy constructor if we don't define our own
        // synthesized copy constructor will copy every non static member into the new object

        // for class type, complier use it's copy constructor
        // for build-in type, just copy
        // for array, complier copies every element of it

        class Foo{
        public:
            Foo(): s("hi"), as{"hi", "hello"} { }
            string s;
            string as[10];
        };
        Foo fa = Foo();
        Foo fb(fa);
        cout << "a's string address: " << &(fa.s) << " b's string address: " << &(fb.s) << endl;
        cout << "b's array address: " << &(fa.as) << " b's array address: " << &(fb.as) << endl;
    }

    // copy initilization
    {
        string dots(10, '.');       // direct initialization
        string s(dots);             // direct initialization
        string s2 = dots;           // copy initialization
        string null_book = "9-9-9";   // copy initialization
        string ninies = string(100, '9');   // copy initialization

        auto foo = [](string s)
        {
            cout << "non reference version: parameter string address is " << &s << endl;
            string ret = string(s);
            cout << "non reference version: returned string address is " << &ret << endl;
            return ret;
        };

        // not only in using '=' defining variables
        // also:
        // 1. non reference parameter in function
        // 2. return type is non reference
        // 3. use {} to initilaize objects, like string a{"1", "2", "3"}
        cout << "the origin string address is " << &dots << endl;   // the origin string address is 000000FA00B4F6B8
        string dots1 = foo(dots);
        // non reference version: parameter string address is 000000FA00B4F858
        // non reference version: returned string address is 000000FA00B4F218
        cout << "the final string address is " << &dots1 << endl;   // the final string address is 000000FA00B4F818

        // so by calling `string foo(string)`, there are 3 copy construction happends:
        // 1: copy constructing the foo's parameter
        // 2: copy constructing inside foo: constructing ret by arguments
        // 2: the rvalue `ret`, copy into the lvalue `dots1`
    }

    // why copy constructor use reference parameter
    {
        // because use non reference type need call copy constructor, but we are defining copy constructor, so it will be a endless loop
    }

    // limitation
    {
        // vector's copy constructor is explicit, so we must use a vector object as parameter
        // different from the direct constructor
        vector<int> v1(10);     // direct initialize accpet int
        //vector<int> v2 = 10;    // no suitable constructor exists to convert from "int" to "std::vector<int, std::allocator<int>>
        vector<int> v3 = vector<int>(10);   // correct
    }

    // compiler can bypass copy constructor
    {
        // replace string `a = "123"` with `string a("123")`
        // but even complier can bypass, we have to make sure the copy constructor exits and accessable
    }
}