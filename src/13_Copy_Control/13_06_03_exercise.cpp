#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;


class Foo{
public:
    Foo& operator=(const Foo&) &;       // only can be called by lvalue
    Foo sorted() const &;
    Foo sorted() &&;
private:
    vector<int> data;
};

Foo& Foo::operator=(const Foo& rhs) &{
    return *this;
}

Foo Foo::sorted() &&{
    cout << "sorted: rvalue version" << endl;
    sort(data.begin(), data.end());
    return *this;
}

#define _13_57_

#ifdef _13_56_
Foo Foo::sorted() const &
{
    cout <<  "sorted: 13.56 const or lvalue version" << endl;
    Foo ret(*this);
    return ret.sorted();
}
#elif  defined(_13_57_)
Foo Foo::sorted() const &
{
    return Foo(*this).sorted();
}
#else
Foo Foo::sorted() const &{
    cout << "sorted: const or lvalue version" << endl;
    Foo ret(*this);
    sort(ret.data.begin(), ret.data.end());
    return ret;
}
#endif


int main()
{
    // 13.56    
    Foo f1;
    f1.sorted();
    // recursive on all control paths

    // 13.57
    // copy construct an Foo object, it's an rvalue, and sort & return this r value
    // correct

    // 13.58
    // see above
    return 0;
}