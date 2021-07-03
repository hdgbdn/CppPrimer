#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

struct LongDouble {
    LongDouble(double = 0.0) { cout << "LongDouble: construct with double" << endl; }
    operator double() { cout << "LongDouble: convert to double" << endl; return 0.0;};
    operator float(){ cout << "LongDouble: convert to float" << endl; return 0.0;};
};

void calc(int){
    { cout << "calc: int version" << endl; };
    return;
}

void calc(LongDouble){
    { cout << "calc: LongDouble version" << endl; };
    return;
}

int main()
{
    // 14.50
    LongDouble ldObj;
    // int ex1 = ldObj;         // since there are two way to convert to build-in arithmetic type, so there is ambiguity
    float ex2 = ldObj;          // correct, exact match, convert to float

    // 14.51
    double dval = 0.0;
    calc(dval);                 // arithmetic conversion is in higher level than class conversion
    return 0;
}