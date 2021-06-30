#include <memory>
#include <string>
#include <functional>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

class StrBlobPtr;
class StrBlob;

class StrBlob{
    friend class StrBlobPtr;
    friend class ConstStrBlobPtr;
public:
    typedef vector<string>::size_type size_type;
    StrBlob();
    StrBlob(initializer_list<string> il);
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
    
    StrBlobPtr begin();
    StrBlobPtr end();
private:            
    shared_ptr<vector<string>> data;
    void check(size_type i, const string &msg) const;
};


class StrBlobPtr{
public:
    StrBlobPtr(): curr(0) { }
    StrBlobPtr(StrBlob &a, size_t sz = 0): wptr(a.data), curr(sz) { }
    string& deref() const;
    StrBlobPtr& incr();
protected:
    shared_ptr<vector<string>> check(size_t, const string&) const;
    weak_ptr<vector<string>> wptr;
    size_t curr;
};

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


StrBlobPtr StrBlob::begin() {return StrBlobPtr(*this);};
StrBlobPtr StrBlob::end() {return StrBlobPtr(*this, data->size());};

shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string &msg) const
{
    auto ret = wptr.lock();
    if(!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if(i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

string& StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr()
{
    auto p = check(curr, "incrememt past end of StrBlobPtr");
    ++curr;
    return *this;
}

class ConstStrBlobPtr{
public:
    ConstStrBlobPtr(): curr(0) { }
    ConstStrBlobPtr(const StrBlob &a, size_t sz = 0): wptr(a.data), curr(sz) { }
    const string& deref() const;
    ConstStrBlobPtr& incr();
protected:
    shared_ptr<vector<string>> check(size_t, const string&) const;
    weak_ptr<vector<string>> wptr;
    size_t curr;
};

shared_ptr<vector<string>> ConstStrBlobPtr::check(size_t i, const string &msg) const
{
    auto ret = wptr.lock();
    if(!ret)
        throw std::runtime_error("unbound ConstStrBlobPtr");
    if(i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

const string& ConstStrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

ConstStrBlobPtr& ConstStrBlobPtr::incr()
{
    auto p = check(curr, "incrememt past end of StrBlobPtr");
    ++curr;
    return *this;
}


int main()
{
    // 12.19

    // 12.20
    {
        StrBlob b;
        string s;
        while(getline(cin, s))
        {
            if(s == "")
                break;
            b.push_back(s);
        }
        StrBlobPtr p(b);
         for (StrBlob::size_type pos = 0; pos != b.size(); ++pos, p.incr())
                std::cout << pos + 1 << ":\t" << p.deref() << std::endl;
    }

    // 12.21
    {
        // both are correct, but the first one is more clear
    }

    // 12.22
    {
        const StrBlob cb{"this", "blob"};
        ConstStrBlobPtr p_cb(cb);
        
        for (auto p = p_cb; ; p.incr())
            std::cout << "deref: " << p.deref() << std::endl;

    }
}