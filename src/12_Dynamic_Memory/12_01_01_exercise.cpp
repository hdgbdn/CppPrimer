#include <memory>
#include <string>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

shared_ptr<string> factory(string s)
{
    return make_shared<string>(s);
}

class StrBlod{
public:
    typedef vector<string>::size_type size_type;
    StrBlod();
    StrBlod(initializer_list<string> il);
    size_type size() const {return data->size();}   // const member function: `this` pointer will be a pointer point to a const
                                                    // so the other function can not change the value returned
    bool empty() const {return data->empty();}
    void push_back(const string &t) {data->push_back(t);}
    void pop_back();
    int data_use_count() const {return data.use_count();};
    string& front();
    string& back();
    string& front() const;
    string& back()  const;
private:            
    shared_ptr<vector<string>> data;
    void check(size_type i, const string &msg) const;
};

StrBlod::StrBlod() : data(make_shared<vector<string>>()) {}
StrBlod::StrBlod(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}

void StrBlod::check(size_type i, const string &msg) const
{
    if(i > data->size())
        throw out_of_range(msg);
}

string& StrBlod::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}

string& StrBlod::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}

string& StrBlod::front() const
{
    check(0, "front on empty StrBlob");
    return data->front();
}

string& StrBlod::back() const
{
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlod::pop_back()
{
    check(0, "pop back on empty StrBlob");
    data->pop_back();
}

int main()
{
    StrBlod b1;
    {
        StrBlod b2 = {"a", "an", "the"};
        cout << "b1 size after b2 construction " << b1.size() << endl;          // 0
        cout << "b2 size after construction " << b2.size() << endl;             // 3
        b1 = b2;
        cout << "b1 size after assign to b2 " << b1.size() << endl;             // 3
        cout << "b2 size after assign to b1 " << b2.size() << endl;             // 3
        b2.push_back("about");
        cout << "b1 size after b2 push a new element " << b1.size() << endl;    // 4
        cout << "b2 size after push a new element " << b2.size() << endl;       // 4
    }
    cout << "b1 size after b2 leave it's scope " << b1.size() << endl;          // 4
    const StrBlod& b3(b1);
    cout << "const version of `front`: " << b3.front() << endl;
}

// 12.4: because i is unsigned type

// 12.5: can use { "x", "xx"} to initialize a StrBlod object