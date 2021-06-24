#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

// 1. =default only can used in default construcotor and copy control member,(copy constructor & copy assignment)and destructor
class A{
        A() = default;              // inline
        A(const A& ) = default;     // inline
        A& operator=(const A& );
        ~A() = default;             // inline
    };
A& A::operator=(const A&) = default;    // not inline

int main()
{
    
    return 0;
}