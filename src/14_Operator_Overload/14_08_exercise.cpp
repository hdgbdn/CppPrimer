#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

template<typename T>
class IfThenElse {
public:
    T operator()(bool a, T b, T c){
        if(a) return b;
        else return c;
    }
};

class PrintString{
public:
    string operator()(istream& is){
        string ret = string();
        if(is) is >> ret; 
        return ret;
    }
};

class StringVector{
public:
    vector<string> operator()(istream& is){
        vector<string> vret;
        string s;
        while(getline(is, s)){
            vret.push_back(s);
        }
        return vret;
    }
};

class CheckEqual
{
public:
    CheckEqual(int v): val(v) {}
    bool operator()(int rhs)
    {
        return val == rhs;
    }
private:
    int val;
};

int main()
{
    // 14.33
    // since it is a member function, and member function don't has limitation of parameters

    // 14.34
    IfThenElse<string> ite;
    cout << ite(1>0, "yes 1 > 0", "no 1 < 0") << endl;  // "yes 1 > 0"

    // 14.35
    PrintString ps;
    cout << "ps(cin) " << ps(cin) << endl;

    // 14.36
    // StringVector sv;
    // vector<string> vs = sv(cin);
    // for_each(vs.begin(), vs.end(), [](string s){ cout << s << " "; });

    // 14.37
    vector<int> vi {1,2,3,4,5,6,7,8,9,0};
    int oldNum;
    int newNum;
    cin >> oldNum >> newNum;
    replace_if(vi.begin(), vi.end(), CheckEqual(oldNum), newNum);
    for_each(vi.begin(), vi.end(), [](int i){ cout << i << " "; });

    return 0;
}