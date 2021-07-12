#include <iostream>
#include <string>

using namespace std;

int main()
{
    // how to store base or dervied objects into stl containers?
    // if directly store the object itself, then
    // 1: use base type, the dervied parts will be cut off
    // 2: use derived type, if store base type, than the derived part is unkonwn

    // solution: store base pointer(recommand smart pointer)
    
}