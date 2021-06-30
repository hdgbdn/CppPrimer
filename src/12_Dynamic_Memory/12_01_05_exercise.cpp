#include <memory>
#include <string>
#include <functional>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    //-- 12.16
    {
        unique_ptr<int> p1(new int(42));
        // function "std::unique_ptr<_Ty, _Dx>::unique_ptr(const std::unique_ptr<_Ty, _Dx> &) [with _Ty=int, _Dx=std::default_delete<int>]" 
        // cannot be referenced -- it is a deleted function
        // unique_ptr<int> p2(p1);      
        unique_ptr<int> p3;
        // function "std::unique_ptr<_Ty, _Dx>::operator=(const std::unique_ptr<_Ty, _Dx> &) [with _Ty=int, _Dx=std::default_delete<int>]"
        // cannot be referenced -- it is a deleted function
        // p3 = p1;
    }

    //-- 12.17
    {
        int ix = 1024, *pi = &ix, *pi2 = new int(2048);
        typedef unique_ptr<int> IntP;

        // IntP p0(ix);                // error, not inited by a new allocated memory
        IntP p1(pi);                // correct
        IntP p2(pi2);               // correct
        // IntP p3(&ix);               // error, ix is not dynamically allocated
        IntP p4(new int(2048));     // correct
        IntP p5(p2.get());          // can pass compile, but two unique pointer point to the same memory.
    }
}