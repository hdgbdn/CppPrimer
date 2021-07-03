#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class SmallInt{
    friend SmallInt operator+(const SmallInt&, const SmallInt&);
public:
    SmallInt(int i = 0): val(i) {};
    operator int() const { return val;}
private:
    size_t val;
};

SmallInt operator+(const SmallInt& lhs, const SmallInt& rhs){
    cout << "SmallInt non-member operator+" << endl;
    return SmallInt();
}

struct LongDouble{
    LongDouble operator+(const SmallInt&) { cout << "LongDouble member operator+" << endl; return LongDouble();}
};
LongDouble operator+(LongDouble &, double){
    cout << "LongDouble non-member operator+" << endl;
    return LongDouble();
}

int main()
{
    // 14.52
    SmallInt si;
    LongDouble ld;
    // ld = si + ld;        // for SmallInt operator+(const SmallInt&, const SmallInt&), there is no way to convert LonDouble to SmallInt
                            // for LongDouble LongDouble::operator+(const SmallInt&), rhs don't match
                            // for LongDouble operator+(LongDouble &, double), it event don't match
                            // so there is error
    ld = ld + si;           // for SmallInt operator+(const SmallInt&, const SmallInt&), ld can't convert to SmallInt
                            // for LongDouble LongDouble::operator+(const SmallInt&), matches
                            // for LongDouble operator+(LongDouble &, double), si can convert to int by convert to double
                            // if don't define the member version, it will use the non-member version

    // 14.53
    SmallInt s1;
    // double d = s1 + 3.14;    // illegal, lhs is SmallInt, rhs is double
                                // both `operator+(const SmallInt&, const SmallInt&)` and
                                // `built-in operator+(int, double)` are viable functions
    double d = s1 + SmallInt(3.14);
    return 0;
}