#include <string>
#include <functional>
#include <vector>
#include "12_03_01.h"

using namespace std;

void runQueries(ifstream &infile)
{
    TextQuery tq(infile);
    while (true)
    {
        cout << "enter word to look for, or q to quit: ";
        string s;
        if(!(cin>>s) || s == "q") break;
        QueryResult ret = tq.Search(s);
        ret.print();
    }
    
    return;
}

int main()
{
    ifstream file;
    file.open("text.txt");
    runQueries(file);
    file.close();
    return 0;
}