#include <memory>
#include <string>
#include <functional>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    struct destination
    {
    public:
        int a;
        destination() : a(0) {}
    };

    struct connection
    {
    public:
        destination *d;
        connection(destination *d) : d(d) {}
    };

    auto f = [&](destination& d)
    {
        connection c(&d);
        shared_ptr<connection> p(&c, [](connection* c){
            cout << "mannualy delete after exit function" << endl;
        });
    };
    destination d = destination();
    f(d);
    return 0;
}