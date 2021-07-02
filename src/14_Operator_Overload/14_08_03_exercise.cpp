#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <functional>
#include <map>

using namespace std;

int main()
{
    auto add = [](int i, int j)
    { return i + j; };

    auto minus = [](int i, int j)
    { return i - j; };

    auto diveide = [](int i, int j)
    { return j == 0? 88888888: i / j; };

    auto multi = [](int i, int j)
    { return i * j; };
    auto mod = [](int i, int j)
    { return i % j; };
    map<string, function<int(int, int)>>
        calculator{
            {"+", add},
            {"-", minus},
            {"/", diveide},
            {"*", multi},
            {"%", mod},
        };

    cout << "1 + 2 = " << calculator["+"](1, 2) << endl;
    cout << "1 - 2 = " << calculator["-"](1, 2) << endl;
    cout << "1 * 2 = " << calculator["*"](1, 2) << endl;
    cout << "1 / 2 = " << calculator["/"](1, 2) << endl;
    cout << "1 % 2 = " << calculator["%"](1, 2) << endl;
}