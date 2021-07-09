#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    // copy assign operator
    {
        class Foo{
        public:
            int val;
            Foo(int x = 2): val(x) {}
            Foo(const Foo& f)
            {
                cout << "copy constructor" << endl;
                val = f.val;
            }
            Foo& operator=(const Foo& rhs)      // copy assignment
            { 
                cout << "copy assignment" << endl;
                val *= rhs.val; 
                return *this;
            }
        };

        Foo a, b;
        Foo c(a);       // copy constructor
        b = a;          // copy assignment
        cout << b.val << endl;
    }

    // synthesized copy-assignment operator
    {
        // if a class don't define the user's copy-assignment operator, the compiler will synthesize one for it
    }
    return 0;
}