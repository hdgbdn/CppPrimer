#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class SmallInt{
public:
    SmallInt(int i = 0): val(i)
    {
        if(i < 0 || i > 255)
            throw out_of_range("Bad SmallInt value");
    }
    operator int() const { cout << "conversion to int: " << to_string(val) << endl; return val; }
private:
    size_t val;
};

class ExpilicSmallInt{
public:
ExpilicSmallInt(int i = 0): val(i)
{
    if (i < 0 || i > 255)
        throw out_of_range("Bad SmallInt value");
}
explicit operator int() const
{
    cout << "explicit conversion to int: " << to_string(val) << endl;
    return val;
}

private:
size_t val;
};

int main()
{
    // a special member function
    SmallInt si;
    si = 4;     // implicit covert 4 to SmallInt
    si + 3;     // convert si to int, why not convert 3 to SmallInt? Because the build-in order is higher than user's
    SmallInt sd = 3.14; // 3.14 convert to int 3 as the parameter of constructor
    cout << "si + 3.14: is" << si + 3.14;          // convert si to int, and to double

    // exception
    // operator "<<" shouldn't be used in a istream, but 
    // cin << i;        if istream can convert to bool, then the coverted bool will be promted as int, then becames 1 << i
    // explicit conversion operator:
    ExpilicSmallInt esi = 3;
    // esi + 3;                // no operator "+" matches these operands -- operand types are: ExpilicSmallInt + int
    static_cast<int>(esi) + 3;  // explicit conversion to int: 3

    // convert to bool
    string value;
    while(std::cin >> value);       // cin has a istream operator bool, if instream is good, then return true;
    cout << "finish input" << endl;

    return 0;
}