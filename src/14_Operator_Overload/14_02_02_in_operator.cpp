#include <iostream>
#include <string>

using namespace std;

class A{
friend ostream& operator<<(ostream&, const A&);
friend istream& operator>>(istream&, A&);
public:
    A(int i = 0, string n = "default name", string a = "default address"): id(i), name(n), address(a) {}
private:
    int id;
    string name;
    string address; 
};

ostream& operator<<(ostream& os, const A& a){
    os << a.id << " " << a.name << " " << a.address;
    return os;
}

istream& operator>>(istream& is, A& a){
    is >> a.id >> a.name >> a.address;
    // it's nessery to check validation of input, if got error input, better to reset the object;
    if(!is) a = A();
    return is;
}

int main()
{
    A a(1, "jim", "Japan");
    cin >> a;
    cout << a;
    // it's nessery to check validation of input, if got error input, better to reset the object;
    return 0;
}