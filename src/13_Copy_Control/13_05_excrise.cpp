#include <iostream>
#include <string>
#include <utility>
#include <memory>
#include <functional>
#include <algorithm>

using namespace std;

// a simple version of vector

class StrVec{
public:
    StrVec(): elements(nullptr), first_free(nullptr),cap(nullptr) {}
    StrVec(initializer_list<string>);
    StrVec(const StrVec&);
    StrVec& operator=(const StrVec&);
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


pair<string*, string*> StrVec::alloc_n_copy(const string* b, const string* e)
{
    auto data = alloc.allocate(e - b);
    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free()
{
	/*
    if(!elements) return;
    for(auto p = first_free; p != elements; )
        alloc.destroy(--p);
    alloc.deallocate(elements, cap - elements);
	 */

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

allocator<string>  StrVec::alloc;

int main()
{
    StrVec s;
    s.push_back("hi");
    s.Print();
    s.resize(10, "no");
    s.resize(4, "no");
    s.Print();
    s.resize(0, "no");
    s.Print();
    s.reserve(10);
    s.Print();
    s.reserve(20);
    s.Print();
    StrVec s2{"hi", "hello", "world"};
    s2.Print();

	// 13.41
	// first_free is pointed to the next element of the last real element
	// if use ++first_free, then it actually use the next of next of the last real element;

	// 13.42

	// 13.43
	// I prefer the for_each-lambda version, because it is more modern
    return 0;
}