#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

class numbered_1{
public:
    static int lastSn;
    int mysn;
    numbered_1(): mysn(lastSn++) {}
};

int numbered_1::lastSn = 0;


class numbered_2{
public:
    static int lastSn;
    int mysn;
    numbered_2(): mysn(lastSn++) {}
    numbered_2(const numbered_2& n): mysn(lastSn++) {}
};

int numbered_2::lastSn = 0;

int main()
{
    // 13.14
    {
        cout << "13.14 start" << endl;
        auto f = [](numbered_1 s){ cout << s.mysn << endl; };
        numbered_1 a, b = a, c = b;
        f(a); f(b); f(c);   // 0, 0, 0
        cout << "13.14 end" << endl;
    }

    // 13.15
    {
        cout << "13.15 start" << endl;
        auto f = [](numbered_2 s){ cout << s.mysn << endl; };
        numbered_2 a, b = a, c = b;         // copy constructor  1, 2, 3
        f(a); f(b); f(c);                   // 3, 4, 5, because pass value called copy assignment
        cout << "13.15 end" << endl;
    }

    // 13.16
    {
        cout << "13.16 start" << endl;
        auto f = [](const numbered_2& s){ cout << s.mysn << endl; };
        numbered_2 a, b = a, c = b;         // copy constructor  6, 7, 8
        f(a); f(b); f(c);                   // 6, 7, 8
        cout << "13.16 end" << endl;
    }

    return 0;
}