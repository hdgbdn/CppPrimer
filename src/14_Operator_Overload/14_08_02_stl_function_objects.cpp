#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

int main()
{
    // stl defines function objects for us
    plus<int> intAdd;
    negate<int> intNegate;
    int sum = intAdd(10, 20);
    cout << "intAdd(10, 20): " << sum << endl;
    sum = intNegate(intAdd(10, 20));
    cout << "intNegate(intAdd(10, 20)): " << sum << endl;
    sum = intAdd(10, intNegate(10));
    cout << "intAdd(10, intNegate(10)): " << sum << endl;

    // usage of stl function objects
    // change default operator in algorithm
    vector<string> svec{"hi", "hello", "nihao", "konichiwa", "hola"};
    sort(svec.begin(), svec.end(), greater<string>());
    for(auto s: svec) cout << s << " ";
    cout << endl;

    // for pointers
    vector<string *> nameTable {new string("123"), new string("456")};
    sort(nameTable.begin(), nameTable.end(), [](string *a, string *b) {return a < b; });        // compaire pointer is undifined
    sort(nameTable.begin(), nameTable.end(), less<string *>());                                 // but stl can
    return 0;
}