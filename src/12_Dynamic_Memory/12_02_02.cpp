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
    // allocator class
    {
        // `new` and `delete` allocate and construct objects
        // but what if we only need the memory space, and want to assign value later?
        string *const p = new string[10];
        string s;
        string *q = p;
        cout << "enter string " << endl;
        while(cin >> s && q != p + 10)
            *q++ = s;
        const size_t size = q - p;
        cout << "size is " << size << endl;
        delete[] p;                         // remember we can delete a dynamic allocated const object
        // no need to initialize all the allocated space

        allocator<string> alloc;            // define an allocator
        auto const pa = alloc.allocate(10);  // use allocator to allocate raw memory
        alloc.deallocate(pa, 10);
    }

        // speed test
    {
        const int N = 10000000;
        auto start = high_resolution_clock::now();
        string *const pn = new string[N];
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);      
        delete[] pn;
        cout  << "use new to allocate " << N << " string, time is " << duration.count() << endl;  

        
        allocator<string> alloc;
        start = high_resolution_clock::now();
        auto const pa = alloc.allocate(N);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        alloc.deallocate(pa, N);
        cout  << "use allocator to allocate " << N << " string, time is " << duration.count() << endl;  
        // use new to allocate 1000000 string, time is 150859
        // use allocator to allocate 1000000 string, time is 6076
        // 20x time difference
    }

    // unconstructed memory
    {
        const int N = 100;
        allocator<string> alloc;
        auto const p = alloc.allocate(N);   // q point to the first element in the allocated array
        auto q = p;
        alloc.construct(q++);               // default constructor      :""
        alloc.construct(q++, "hi");         // value initializion       :"hi"
        alloc.construct(q++, 10, 'c');      // like string(10, 'c');    :"cccccccccc"
        cout << *(p) << endl;
        cout << *(p + 1) << endl;
        cout << *(p + 2) << endl;
        // cout << *q << endl;              // fatal error, unconstructed memory

        // destroy initialized element
        // alloc.destroy(p + 10);           // error, only can destroy constructed element
        while(q != p)
            alloc.destroy(--q);

        // free memory
        // N must be same as allocated
        alloc.deallocate(p, N);
    }

    // create objects in unconstructed memory
    {
        const int N = 100;
        allocator<int> alloc;
        vector<int> vi(N, 99);
        auto p = alloc.allocate(N * 2);
        auto q = uninitialized_copy(vi.begin(), vi.end(), p);   // q point to the next element of last copied element
        q = uninitialized_fill_n(q, vi.size(), 42);
        for(auto m = p; m != q; m++)
            cout << *m << '\t';
        alloc.deallocate(p, N);
    }
}