#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "13_04_Message.h"

using namespace std;

int main()
{
    // 13.33
    // because we want to change the actual floder's data
    // use const, we can't modify data, don't use referenct, we just can change a local variable

    // 13.34s

    // 13.35
    // use synthesized copy control, we can't tell floders to add the copied messages or delete the origin message

    // 13.36

    // 13.37
    Message hello("hello"), hi("hi"), hey("hey");
    Folder f1("floder1"), f2("floder2"), f3("floder3");
    hello.save(f1);
    hello.save(f2);
    f1 = f2;
    f1.Print(); f2.Print();
    hi = hello;
    hi.Print();

    // why don't use copy swap in copy-assignment?
    // current version just some set operation no objects created or destroied
    // but in copy assign will construct twice and destruct twice
    return 0;
}