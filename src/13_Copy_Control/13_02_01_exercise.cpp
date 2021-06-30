#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

class StrBlob{
public:
    typedef vector<string>::size_type size_type;
    StrBlob();
    StrBlob(initializer_list<string> il);
    StrBlob(const StrBlob&);
    StrBlob& operator=(const StrBlob&);
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

StrBlob::StrBlob(const StrBlob& sb):data(make_shared<vector<string>>(*sb.data)){}

StrBlob& StrBlob::operator=(const StrBlob& rhs)
{
    shared_ptr<vector<string>> copydata = make_shared<vector<string>>(*rhs.data);
    data = copydata;
    return *this;
}

StrBlob::StrBlob() : data(make_shared<vector<string>>()) {}
StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}

void StrBlob::check(size_type i, const string &msg) const
{
    if(i > data->size())
        throw out_of_range(msg);
}

string& StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}

string& StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}

string& StrBlob::front() const
{
    check(0, "front on empty StrBlob");
    return data->front();
}

string& StrBlob::back() const
{
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop back on empty StrBlob");
    data->pop_back();
}

int main()
{
    // 13.23
    // the biggest difference is my version forgot to handle self-assignment, 
    // may cause data loss and memory leak, because delete the memory before cpoy

    // 13.24
    // if not define destructor, ps will leak.
    // if not define copy constructor, differ HasPtr object share same memory,
    // if one of them delete this pointer, all other objects's pointer will be dangling

    // why need copy constructor: allocate and copy memory from the right object, it can't be done only by default copy constructor
    // why need copy-assignment: the same as above
    // why don't need destructor: shared_ptr will automaticlly release the memory; 

    return 0;
}