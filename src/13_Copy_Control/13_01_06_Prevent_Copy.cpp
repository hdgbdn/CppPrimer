#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

int main()
{
    // some class don't need copy control, like iostream
    // how to do this?
    struct NoCopy
    {
        NoCopy() = default;
        NoCopy(const NoCopy&) = delete;
        NoCopy& operator=(const NoCopy&) = delete;
        ~NoCopy() = default;
    };
    

    // should not delete destructor
    struct NoDtor {
    public:
        NoDtor() = default;
        ~NoDtor() = delete;
    };
    // NoDtor nd;      // function "NoDtor::~NoDtor() noexcept" (declared at line 24) cannot be referenced -- it is a deleted function
    NoDtor *p = new NoDtor();
    // delete p;           // function "NoDtor::~NoDtor() noexcept" (declared at line 24) cannot be referenced -- it is a deleted function

    // synthesized copy control member can be deleted
    {
        // if data member cannot defalut construt copy assign or destory, the synthesized function will be defined as deleted
        // member is referen or const, compiler will not synthesize default constructor or copy assignment
        // all above condition, the funtion will be deleted
    }
    
    // before new standrad, private copy control
    class PrivateCopy{
    // no access specifiers: private
        PrivateCopy(const PrivateCopy&);
        PrivateCopy& operator=(const PrivateCopy&);
    public:
        PrivateCopy() = default;
        ~PrivateCopy();
    };
    PrivateCopy pc1;
    //PrivateCopy pc2(pc1);   // "PrivateCopy::PrivateCopy(const PrivateCopy &)" (declared at line 41) is inaccessible
}