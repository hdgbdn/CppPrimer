#include <memory>
#include <string>
#include <functional>
#include <vector>
#include <iostream>
#include <chrono>

using namespace std::chrono;
using namespace std;

int main()
{
    const int N = 100000;
    auto start = high_resolution_clock::now();
    string *const p = new string[N];
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout  << "use new to allocate " << N << " string, time is " << duration.count() << endl;  
    string s;
    string *q = p;
    cout << "enter your string" << endl;
    while(cin >> s && q != p + N)
        *q++ = s;
    delete[] p;

    allocator<string> alloc;
    start = high_resolution_clock::now();
    auto pa = alloc.allocate(N);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout  << "use allocator to allocate " << N << " string, time is " << duration.count() << endl;
    
    cout << "enter your string" << endl;
    while(cin >> s && q != p + N)
        *q++ = s;
    alloc.deallocate(pa, N);
}