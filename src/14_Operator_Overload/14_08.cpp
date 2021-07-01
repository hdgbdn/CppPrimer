#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// operator ()
// behavirours like a function, but actually it's a object
struct absInt{
    int operator()(int val) const{
        return val < 0 ? -val : val;
    }
};

class PrintString{
public:
    PrintString(ostream &o = cout, char c = ' '):
        os(o), sep(c) {}
    void operator()(const string &s) const { os << s << sep; }
private:
    ostream &os;
    char sep;
};

int main()
{
    // what is a function object:
    absInt absOjb;
    cout << "call absInt(-5), result is: " << absOjb(-5) << endl;

    PrintString printer;
    string s("hi");
    printer(s);
    PrintString errors(cerr, '\n');
    printer(s);

    // function objects can be parameter
    vector<string> vs {"hi", "hello", "nihao"};
    // for_each will call the temp object, and the call tempobj.operator(*iterator)
    for_each(vs.begin(), vs.end(), PrintString(cerr, '\n'));
    return 0;
}