#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

int f(){
    return 1;
}

int main()
{
    // 13.45
    // rvalue reference is reference bound to rvalue
    
    // 13.46
    int f();                // f is a name, so lvalue
    vector<int> vi(100);    // vi is a name, so lvalue;
    int&& r1 = f();         // f return a temp value;
    int& r2 = vi[0];        // vi[0] is a non temp value;
    int &r3 = r1;           // r1 now is a non temp value;
    int&& r4 = vi[0] * f(); // vi[0] * f() is a temp value;
}