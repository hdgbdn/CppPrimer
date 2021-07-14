#ifndef _STRVEC_H_
#define _STRVEC_H_

#include <iostream>
#include <string>
#include <utility>
#include <memory>
#include <algorithm>
#include <functional>

using namespace std;

// a simple version of vector

class StrVec{
public:
    StrVec(): elements(nullptr), first_free(nullptr),cap(nullptr) {}
    StrVec(initializer_list<string>);
    StrVec(const StrVec&);
    StrVec::StrVec(StrVec &&s) noexcept;
    StrVec& operator=(const StrVec&);
    StrVec& operator=(StrVec &&rhs) noexcept;
    string operator[](size_t) const;
    ~StrVec();
    void push_back(const string&);
    void pop_back();
    void reserve(size_t); 
    size_t size() const { return first_free - elements; }
    void resize(size_t, const string& = string());
    size_t capacity() const { return cap - elements; }
    string* begin() const { return elements; }
    string* end() const { return first_free; }
    void Print();
private:
    static allocator<string> alloc;
    void chk_n_alloc() { if(size() == capacity()) reallocate(); }
    pair<string*, string*> alloc_n_copy(const string*, const string*);
    void free();
    void reallocate();
    string* elements;
    string* first_free;
    string* cap;
};

void StrVec::push_back(const string& s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

void StrVec::pop_back()
{
    if (elements == first_free) return;
    alloc.destroy(--first_free);
}

string StrVec::operator[](size_t n) const {
    if(n >= size()) return "";
    else return *(elements + n);
}

pair<string*, string*> StrVec::alloc_n_copy(const string* b, const string* e)
{
    auto data = alloc.allocate(e - b);
    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free()
{
    for_each(elements, first_free, [](std::string& p) {alloc.destroy(&p); });
}

StrVec::~StrVec()
{
    free();
}

StrVec::StrVec(initializer_list<string> list): elements(nullptr), first_free(nullptr), cap(nullptr)
{
    for (auto s : list)
        push_back(s);
}

StrVec::StrVec(const StrVec& s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
    return;
}

StrVec& StrVec::operator=(const StrVec& rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}


// very importand: introducion std::move
void StrVec::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = elements;
    for(size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

void StrVec::reserve(size_t n)
{
    if(n <= capacity()) return;
    auto newcapacity = n;
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = elements;
    for(size_t i = 0; i != size(); ++i)
        if(i > newcapacity) break;
        alloc.construct(dest++, std::move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

void StrVec::resize(size_t n, const string& s)
{
    // check if need reallocate and re allocate
    if(n > capacity())
    {
        auto newcapacity = n;
        auto newdata = alloc.allocate(newcapacity);
        auto dest = newdata;
        auto elem = elements;
        for(size_t i = 0; i != size(); ++i)
            if(i > newcapacity) break;
            alloc.construct(dest++, std::move(*elem++));
        free();
        elements = newdata;
        first_free = dest;
        cap = elements + newcapacity;
    }
    if(n > size()){
        size_t len = n - size();
        first_free = uninitialized_fill_n(first_free, len, s);
    }
    else{
        size_t len = size() - n;
        auto p = first_free;
        for(size_t i = len; len > 0; len--){
            alloc.destroy(--p);
            first_free = p;
        }
    }
}

void StrVec::Print()
{
    cout << "size is " << size() << " capacity is " << capacity() << endl;
    cout << "elements are ";
    for(auto p = elements; p != first_free; p++)
        cout << *p << ' ';
    cout << endl;
}

// here is the move constructor
StrVec::StrVec(StrVec &&s) noexcept: elements(s.elements), first_free(s.first_free), cap(s.cap){
    // since move constructor "steal" memory, so it usuall throw except, we use "noexcept" to tell compiler
    // and after stealing memory, the "s" object call it's destructor, so we set these pointer point to nullptr
    // to avoid the stealed memory released by "s"'s destructor
    s.elements = s.first_free = s.cap = nullptr;
}

// here is the move assignment
StrVec& StrVec::operator=(StrVec &&rhs) noexcept{
    if(this != &rhs){
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

allocator<string>  StrVec::alloc;

#endif