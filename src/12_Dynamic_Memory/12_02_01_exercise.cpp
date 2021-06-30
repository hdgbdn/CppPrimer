#include <memory>
#include <string>
#include <functional>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    // 12.23
    {
        const char *a = "Hello";
        const char *b = "World!";
        cout << "len a " << strlen(a) << endl;
        cout << "len b " << strlen(b) << endl;
        char *c = new char[strlen(a) + strlen(b) + 1];
        strcpy(c, a);
        strcat(c, b);
        cout << c << endl;
        delete[] c;
    }

    // 12.23
    {
        string a("hello");
        string b("world!");
        string c = a + b;
        std::cout << c << std::endl;
    }
    
    // 12.24
    {
        cout << "Input string length";
        size_t len;
        cin >> len;
        std::cin.ignore();
        char *ca = new char[len + 1];
        std::cin.get(ca, len + 1);
        std::cout << "The input string is:\n\"" << ca << "\"" << std::endl;
    }
    
    // 12.25
    {
        int *pa = new int[10];
        delete[] pa;
    }
}