#include <memory>
#include <string>
#include <functional>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    // for need like dynamic continuous memory, std container like vector is enough for most application
    // new and array
    {
        int size;
        cin >> size;
        int *pia = new int[size];   // need [] to specify the size of dynamic array, the number inside should be interger
        typedef int arrT[42];
        int *p = new arrT;
        *p = 1;
        cout << "de reference a array is " << *p << endl;
        // after that we just get a elementer type pointer, not an array object, so we don't know the size and other array related information
    }

    // initialization
    {
        // value initialize
        int *pia = new int[10];
        int *pia2 = new int[10]();
        // int *pia2 = new int[10](10);         // a new-initializer may not be specified for an array
        string *psa = new string[10];
        string *psa2 = new string[10]();
        // string *psa = new string[10](hi");   // a new-initializer may not be specified for an array

        int *pia3 = new int[10]{0,1,2,3,4,5,6,7,8,9};   // initializer_list
        string *psa3 = new string[10]{"a", "an", "the", string(3, 'x')};   // initializer_list
    }

    // empty array is legal
    {
        int size;
        cin >> size;
        size_t n = size;
        int* p = new int[n];
        for(int *q = p; q != p + n; q++){
            cout << "if size == 0, will not enter this for loop" << endl;
        }
        delete[] p;
    }

    // unique_ptr and dynamic array
    {
        unique_ptr<int[]> up(new int[10]);
        // *up = 1;     // error, up represents a array, not a single element 
        // no operator "*" matches these operands -- operand types are: * std::unique_ptr<int [], std::default_delete<int []>>
        for(size_t i = 0; i != 10; i++){
            up[i] = i;
            cout << up[i] << endl;
        }
            
        up.release();       // automatic free the array

        // must provide a deleter
        shared_ptr<int> sp(new int[10], [](int *p){
            cout << "delete by delete function" << endl;
            delete[] p;
            });

        for(size_t i = 0; i != 10; i++){
            *(sp.get() + i) = i;
            cout << "access dynamic array by shared_ptr " << *(sp.get() + i) << '\t';
        }
        sp.reset();
    }
}