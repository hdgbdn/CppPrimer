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
        Foo c(a);
        b = a;
        cout << b.val << endl;
    }

    // synthesized copy-assignment operator
    {
        
    }
    return 0;
}