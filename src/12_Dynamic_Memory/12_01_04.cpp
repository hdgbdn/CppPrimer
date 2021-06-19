#include <memory>
#include <string>
#include <functional>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    // exception
    {
        auto f = []()
        {
            shared_ptr<int> sp(new int(42));
            // exception here

        };// after function is over, sp still can be freed, because leaving scope, sp will automatic be destoried

        auto f2 = []()
        {
            int *p = new int(42);
            // exception here
            delete p;
        };// after function is over, p is leak, p cannot be automatic destoried, the delete code will not be execute
    }


    {
        struct destination{
        public:
            int a;
            destination(): a(0) {}
        };
        
        struct connection
        {
        public:
            destination* d;
            connection(destination* d): d(d) {}
        };
        
        destination d = destination();
        auto connect = [](destination *)->connection
        {
            return connection(nullptr);
        };

        auto f = [&](destination &d)
        {
            connection c = connect(&d);
        };
        // memory leak for struct: connection don't have a destructor
        f(d);

        auto end_connection = [](connection * c)
        {

        };

        auto f1 = [&](destination &d)
        {
            connection c = connect(&d);
            shared_ptr<connection> p(&c, end_connection);
        };
    }
    return 0;
}