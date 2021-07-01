#include <iostream>
#include <string>

using namespace std;

class A{
friend ostream& operator<<(ostream&, const A&);
public:
    A(int i, string n, string a): id(i), name(n), address(a) {}
private:
    int id;
    string name;
    string address; 
};

ostream& operator<<(ostream& os, const A& a){
    os << a.id << " " << a.name << " " << a.address;
    return os;
}

int main()
{
    A jim(10, "jim", "japan");
    cout << jim << endl;
    // "<<" should be non member function
    // because the lhs is ostream, not type.
}