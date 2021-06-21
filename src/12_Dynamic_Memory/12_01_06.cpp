#include <memory>
#include <string>
#include <functional>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    // weak pointer is depended on shared_ptr
    // but it don't add the use count, just act as an observer
    {
        auto p = make_shared<int>(42);
        weak_ptr<int> wp(p);
        // cout << "weak pointer value is " << *wp << endl;     error: no `*` operator
        if(shared_ptr<int> np = wp.lock())
            cout << "get shared_ptr from weak_ptr, value is " << *np << endl;
    }
}