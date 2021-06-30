#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

class Employee{
public:
    int id;
    string name;
    Employee(): id(lastId++), name(string()) {}
    Employee(string name): id(lastId++), name(name) {}
    Employee(const Employee& e): id(lastId++), name(e.name) {}
    Employee& operator=(const Employee& e){name = e.name;}
private:
    static int lastId;
};

int main()
{
    // 13.19
    // need to define its own copy control because we must ensure the id is unique

    // 13.20
    // TextQuery:
    // copy: just copy shared_ptr, the memory allocated for vectors and maps will not be copied
    // assign: same as copy
    // the shared_ptr is destroied, if the count decreased to 0, vectors and maps will also be destroied

    // 13.21
    // don't need, there is no object specified data member
}