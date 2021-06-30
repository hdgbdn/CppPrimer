#include <iostream>
#include <string>
#include <algorithm>
#include "13_04_Message.h"

using namespace std;

class StrVec{
public:
    StrVec(): elements(nullptr), first_free(nullptr),cap(nullptr) {cout << "StrVec: using default construct" << endl;}
    StrVec(initializer_list<string>);
    StrVec(const StrVec&);
    StrVec::StrVec(StrVec &&s) noexcept;
    StrVec& operator=(const StrVec&);
    StrVec& operator=(StrVec &&rhs) noexcept;
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
    for_each(elements, first_free, [](std::string& p) {alloc.destroy(&p); });
}

StrVec::~StrVec()
{
    cout << "StrVec: deconstruct " << endl;
    free();
}

StrVec::StrVec(initializer_list<string> list): elements(nullptr), first_free(nullptr), cap(nullptr)
{
    for (auto s : list)
        push_back(s);
}

StrVec::StrVec(const StrVec& s)
{
    cout << "StrVec: using copy construct" << endl;
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
    return;
}

StrVec& StrVec::operator=(const StrVec& rhs)
{
    cout << "using copy assignment" << endl;
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
    cout << "StrVec: using move assignment" << endl;
    // since move constructor "steal" memory, so it usuall throw except, we use "noexcept" to tell compiler
    // and after stealing memory, the "s" object call it's destructor, so we set these pointer point to nullptr
    // to avoid the stealed memory released by "s"'s destructor
    s.elements = s.first_free = s.cap = nullptr;
}

// here is the move assignment
StrVec& StrVec::operator=(StrVec &&rhs) noexcept{
    cout << "StrVec: using move assignment" << endl;
    if(this != &rhs){
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

allocator<string>  StrVec::alloc;

StrVec func1(){
    cout << "enter func1" << endl;
    return StrVec();    // construct a rvalue, then assign to the lvalue outside function, and destruct this rvalue
}

StrVec func2(){
    cout << "enter func2" << endl;
    StrVec ret = StrVec();          // default construct a lvalue
    cout << "func2 finish StrVec ret = StrVec()" << endl;
    return ret;     // ret is lvalue, so it will be copied to an rvalue and return!!!!
}
//--------------------
struct X {
    int i;
    string s;
};
struct hasX{
    X mem;
};

//--------------------
class Foo{
public:
    Foo() = default;
    Foo(const Foo& x) {cout << "using Foo copy constructor" << endl;}
};

//--------------------
class HasPtr
{
    friend void swap(HasPtr &, HasPtr &);
public:
    HasPtr(const string &s = string()) : ps(new string(s)), i(0) {cout << "HasPtr default constructor" << endl;}
    // if add a move constructor, then the copy assignment will also became move assignment
    HasPtr(HasPtr&& p) noexcept: ps(p.ps), i(p.i) {p.ps = nullptr; cout << "HasPtr move constructor" << endl;}
    HasPtr(const HasPtr &ptr) : ps(new string(*ptr.ps)), i(ptr.i) {cout << "HasPtr copy constructor" << endl;}
    HasPtr& operator=(HasPtr rhs){cout << "HasPtr copy assignment" << endl; swap(*this, rhs); return *this; }
    ~HasPtr() { delete ps; }

private:
    string *ps;
    int i;
};

inline
void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}

int main()
{
    // why have to tell compiler noexcept in move constructor?
    // in stl container, vector ensure if a exception happends in push_back
    // vector itself will not be affected
    // so , if use move constuctor, when exception occurs, the origin object is changed
    // and the destination object may be incomplete, so it will change vector itself -- vector may have a broke object
    // it breaks the promise. but if use copy constructor, if exception occurs,
    // the old element remain unchanged, and the error construction
    // can be easily released. so vector prefer to use copy constructor.
    // but if move constructor add noexcept, vector can use it since we claim it will not throw exception

    
    // keep source object deconstructable after move it
    // because after move, the source object will be destoried

    // class don't defined any copy control member and every non static data member can be moved, copiler will 
    // synthesize move constuctor or move assignmenty
    X x, x2 = std::move(x);
    hasX hx, hx2 = std::move(hx);

    // we can't define move(constructor or assignment) to a deleted function, but if we ask compiler to 
    // generate =default version move, and no all member can be move, than compiler will define move as deleted

    // move rvalue, copy lvalue
    StrVec v1, v2;
    v1 = v2;        // using copy assignment
    v2 = func1();   // using default construct to construct the returned rvalue, using move assignment to assign v2
    cout << "finish func1" << endl;
    v2 = func2();   // if use temp to store the StrVec() returned rvalue, then the temp should be move construct a new rvalue
    // and return!!!!!!!!!!
    cout << "finish func2" << endl;


    // complier will use copy to replace move
    {
        Foo x;
        Foo y(x);               // using Foo copy constructor
        Foo z(std::move(x));    // using Foo copy constructor

        // I think move is a optimisation of copy
        // it may trade safety for speed
        // if there is no move operation, use copy is okay
    }

    // copy and swap version of move
    {
        HasPtr hp2;                 // HasPtr default constructor
        HasPtr hp = hp2;            // HasPtr copy constructor
        hp = hp2;                   // HasPtr copy constructor, HasPtr copy assignment: first copy construct as '=' parameter, then copy assign
        hp = std::move(hp2);        // HasPtr move constructor, HasPtr copy assignment: first move construct as '=' parameter, then copy assign

        // ENDLESS lOOPING WARNGING!
        // if don't define my own swap function, it will enter an endless loop
        // because copy assign uses std::swap, and std::swap use copy assign to temp var
        // it becames a endless loop
    }

    // test message move constructor and move assignment
    {
        // since both move constructor and move assignment need move folder from an rvalue
        // the function moves a Message object's set, and remove the rvalue from folders and add this
        // at the end, empty the set in the rvalue, because although it is valid, the elements are unknow
        /*
        void Message::move_Folders(Message* m){
            folders = std::move(m->folders);
            for(auto f : folders){
                f->remMsg(m);
                f->addMsg(this);
            }
            m->folders.clear();
        }
        */

       // and since set don't prefer the nonexcption one, and in f->addMsg may cause bad_alloc
       // so we don't add noexcept here
       /*
        Message::Message(Message &&m): contents(std::move(m.contents)){
            move_Folders(&m);
        }
       */
        Message m1;
        Message m2 = Message();     // not default construct, it's move construct
        m2 = std::move(m1);
    }

    // move iterator
    {
        /*
        void StrVec::reallocate()
        {
            auto newcapacity = size() ? 2 * size() : 1;
            auto newdata = alloc.allocate(newcapacity);
            auto dest = newdata;
            auto elem = elements;
            for (size_t i = 0; i != size(); ++i)
                alloc.construct(dest++, std::move(*elem++));
            free();
            elements = newdata;
            first_free = dest;
            cap = elements + newcapacity;
        }
        */
       // if use uninitialized_copy to move range element
       // auto first = alloc.allocate(newcapacity);
       // atuo last = uninitialized_copy()make_move_iterator(begin()), make_move_iterator(end()), first);
       // the iterator given is a move iterator, returns a rvalue reference
    }

    return 0;
}