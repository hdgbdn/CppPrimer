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
    return SmallInt(lhs.val + rhs.val);
}

// since there can be the member function version of operator and non-member version
// if defined both, there will be ambiguity
int main()
{
    SmallInt s1, s2;
    SmallInt s3 = s1 + s2;
    // int i = s3 + 0;     // ambiguity: convert s3 to int, or s3 + SmallInt(0), then convert to int?
    // the build-in highest order is conversion between build-in types, not user type to build-in or build-in to user type
    return 0;
}