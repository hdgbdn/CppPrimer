#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <functional>
#include <map>

using namespace std;

int add(int i, int j){ return i + j; }
auto mod = [](int i, int j) { return i % j; };
struct divide {
    int operator()(int denominator, int divisor){
        return denominator / divisor;
    }
};

int main()
{
    // function, function pointer, lambda, bind, operator()
    // but different callable objects and share same call signature:
    // like int(int, int): return type, parameters' type

    // but if we want to contain them?
    map<string, int(*)(int, int)> oldbinops;       // just can store function pointer
    oldbinops.insert({"+", add});                  // correct, function pointer
    oldbinops.insert({"%", mod});                  // ???????? book says it's error, but it can pass compiler and works well???????
    cout << oldbinops["%"](10, 3) << endl;         

    // oldbinops.insert({"%", divide()});          // error: object is not function pointer

    // that's why function <T> exits:
    function <int(int, int)> f1 = add;
    function <int(int, int)> f2 = divide();
    function <int(int, int)> f3 = [](int i, int j){ return i * j; };

    map<string, function<int(int, int)>> binops{
        {"+", add},
        {"-", minus<int>()},
        {"/", divide()},
        {"*", [](int i, int j){return i * j;}},
        {"%", mod},
    };

    cout << "binops[\"+\"](10, 5) = " << binops["+"](10, 5) << endl;
    cout << "binops[\"-\"](10, 5) = " << binops["-"](10, 5) << endl;
    cout << "binops[\"/\"](10, 5) = " << binops["/"](10, 5) << endl;
    cout << "binops[\"*\"](10, 5) = " << binops["*"](10, 5) << endl;
    cout << "binops[\"%\"](10, 5) = " << binops["%"](10, 5) << endl;

    // overloaded function and function 
    // ambiguity
    divide add = divide();
    // now we have two different callable objects with same name, 
    binops.insert({"1", add});       // insert which one?
    cout <<"binops[\"1\"](10, 5) = " << binops["1"](10, 5) << endl;     // use the divide one
    // one way is using function pointer
    // int (*fp)(int, int) = add;
    // binops.insert({"1", fp});

    // or use lambda
    // binops.insert({"1", [](int a, int b){ return add(a, b)}]});
    return 0;
}