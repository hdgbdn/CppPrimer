#include <memory>
#include <string>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

// 12.6
vector<int>* Create()
{
    vector<int> *p = new vector<int>();
    return p;
}

void Input(vector<int> *vi)
{
    int i;
    while (cin >> i)
    {
        vi->push_back(i);
    }
}

void Output(vector<int> *vi)
{
    for(auto i : *vi)
        cout << i << endl;
}

shared_ptr<vector<int>> SharedCreate()
{
    shared_ptr<vector<int>> shared_vi = make_shared<vector<int>>();
    return shared_vi;
}

void SharedInput(shared_ptr<vector<int>> vi)
{
    int i;
    while (cin >> i)
    {
        vi->push_back(i);
    }
}

void SharedOutput(shared_ptr<vector<int>> vi)
{
    for(auto i : *vi)
        cout << "shared ptr: " << i << endl;
}

bool b()
{
    int* p = new int;
    return p;
    // wrong! after returning value, no pointer are pointing to the allocated int, memory leaked
}
int main()
{
    //vector<int> *vi1 = Create();
    //Input(vi1);
    //Output(vi1);

    auto vi2 = SharedCreate();
    SharedInput(vi2);
    SharedOutput(vi2);

    int *q = new int(42), *r = new int(100);
    r = q;      // memory leak
    auto q2 = make_shared<int>(42), r2 = make_shared<int>(100);
    r2 = q2;    // no leak, when r2 is pointed to new memory, the previous memory is freed

    return 0;
}