#include <iostream>
#include <string>

using namespace std;

class A{
friend ostream& operator<<(ostream&, const A&);
friend istream& operator>>(istream&, A&);
friend A operator+(const A&, const A&);
friend bool operator==(const A&, const A&);
friend bool operator!=(const A&, const A&);
friend bool operator<(const A&, const A&);
friend bool operator>(const A&, const A&);
public:
    A(int i = 0, string n = "default name", string a = "default address"): id(i), name(n), address(a) {}
    A& operator+=(const A&);
    A& operator=(initializer_list<int>);
    string& operator[](size_t);
    const string& operator[](size_t) const;
    A& operator++();
    A operator++(int);         // postfix version
    A& operator--();
    A operator--(int);         // postfix version
    int& operator*();
    string* operator->();
private:
    int id;
    string name;
    string address; 
};

A& A::operator+=(const A& rhs){
    id += rhs.id;
    name += rhs.name;
    address += rhs.address;
    return *this;
}

ostream& operator<<(ostream& os, const A& a){
    os << a.id << " " << a.name << " " << a.address;
    return os;
}

istream& operator>>(istream& is, A& a){
    is >> a.id >> a.name >> a.address;
    if(!is) a = A();
    return is;
}

A operator+(const A& lhs, const A& rhs){
    A ret = lhs;
    ret += rhs;
    return ret;
}

bool operator==(const A& lhs, const A& rhs)
{
    return lhs.id == rhs.id &&
            lhs.name == rhs.name &&
            lhs.address == rhs.address;
}

bool operator!=(const A& lhs, const A& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const A& lhs, const A& rhs){
    return lhs.id < rhs.id;
}

bool operator>(const A& lhs, const A& rhs){
    return (lhs != rhs) && !(lhs < rhs);
}

A& A::operator=(initializer_list<int> il){
    auto i = il.begin();
    if(i != il.end()) id = *i++;
    if(i != il.end()) name = to_string(*i++);
    if(i != il.end()) address = to_string(*i++);
    return *this;
}

string& A::operator[](size_t n){
    return const_cast<string &>(
        static_cast<const A &>(*this)[n]);
}

const string& A::operator[](size_t n) const{
    if(n == 0) return name;
    if(n == 1) return address;
}

A& A::operator++(){
    ++id;
    return *this;
}

A A::operator++(int){
    A ret(*this);
    ++*this;
    return ret;
}

A& A::operator--(){
    --id;
    return *this;
}

A A::operator--(int){
    A ret(*this);
    --*this;
    return ret;
}

int& A::operator*(){
    return id;
}

string* A::operator->(){
    return &name;
}

int main()
{
    A a1, a2;
    cout << "a1 equals a2? " << (a1 == a2) << endl;
    cout << "a1 not equals a2? " << (a1 != a2) << endl;
    cout << "a1 + a2: " << (a1 + a2) << endl;
    cout << "a1 += a2: " << (a1 += a2) << endl;
    A a3(10), a4(11);
    cout << "a3 < a4? " << (a3<a4) << endl;
    a3 = {1, 2, 3};
    cout << "a3 after assigned by {1,2,3}: " << a3 << endl;
    const A a5(12);
    cout << "a4[0] is " << a4[0] << " a4[1] is " << a4[1] << endl;
    cout << "a5[0] is " << a5[0] << " a5[1] is " << a5[1] << endl;
    cout << "a4++: " << a4++ << endl;
    cout << "++a4: " << ++a4 << endl;
    cout << "a4--: " << a4-- << endl;
    cout << "--a4: " << --a4 << endl; 
    cout << "a4.operator++(0) " << a4.operator++(0) << endl;

    *a4 = 99;
    cout << "after: *a4 = 99; " << a4 << endl;
    a4->pop_back();
    cout << "after a4->pop_back(); " << a4 << endl;

    // the "->" operator is a little bit different
    // t should return a object's pointer and calls "->" on that object;
    // so obj->mem equals obj.operator()->mem
    // but if we don't define an overloaded "->" operator
    // it just called like (*obj).mem
    return 0;
}