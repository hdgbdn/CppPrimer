#include <iostream>
#include <string>

using namespace std;

int main()
{
    // 15.8
    // dynamic type: the type bound in runtime
    // static type: the type declared

    // 15.9
    // 1: base pointer bound to derived object
    // 2: base reference bound to derived object
    // 3: base pointer copied from a derived pointer

    // 15.10
    // istream& read(istream& is, Sales_data& item)
    // ifstream input; ofstream output;
    // read(input, output);
    // ifstream is derived from istream, and the patameter is istream's reference, so dynamic bounding
    return 0;
}