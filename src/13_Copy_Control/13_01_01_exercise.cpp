#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    // 13.1
    // copy constructor is a constructor that build a new object from a exiting object, using the exiting object's value
    // it accpets a reference of an object

    // 13.2
    // Sales_data::Sales_data(Sales_data rhs);
    // The parameter of the constructor should be a reference
    // To call the copy constructor, we'd need to use the copy constructor to copy the argument, but to copy the argument, we'd need to call the copy constructor, and so on indefinitely.

    // 13.3
    // For StrBlob, the shared_ptr is cpoied, but still pointing to the same vector<string> data, 
    // For StrBlobPtr, the shared_ptr and weak_ptr is cpoied

    // 13.4
    {
        class Point{
        public:
            Point()
            {
                cout << "default constructor" << endl;
            }
            Point(const Point& p)
            {
                cout << "copy constructor" << endl;
            }
            Point& operator=(const Point& rhs)
            {
                cout << "copy assignment" << endl;
                return *this;
            }
        };
        Point global;                           // default constructor
        auto foo_bar = [&](Point arg)->Point    // copy constructor, pass non reference parameter
        {
            cout << "enter foo_bar" << endl;
            Point local = arg;                  // copy constructor
            Point *heap = new Point(global);    // copy constructor
            *heap = local;                      // copy assignment
            Point pa[4] = {local, *heap};       // copy constructor *2, default constructor * 2
            return *heap;
        };
        auto a = foo_bar(global);               // copy constructor, ret val to a
    }

    // 13.5
    {
        class HasPtr{
        public:
            HasPtr(const string &s = string()): ps(new string(s)), i(0){}
            HasPtr(const HasPtr& ptr): ps(new string(*ptr.ps)), i(ptr.i){}
        private:
            string* ps;
            int i;
        };
    }
}