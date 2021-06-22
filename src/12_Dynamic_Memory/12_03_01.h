#ifndef _12_03_H_
#define _12_03_H_
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <memory>

using namespace std;

class QueryResult{
public:
    int line_no;
    QueryResult(string s, shared_ptr<set<int>> l, shared_ptr<vector<string>> f): s(s), lines(l), file(f) {};
    void print();
private:
    string s;
    shared_ptr<set<int>> lines;
    shared_ptr<vector<string>> file;
};

class TextQuery{
public:
    TextQuery(ifstream&);
    QueryResult Search(const string&);
private:
    shared_ptr<vector<string>> file;
    map<string, shared_ptr<set<int>>> wm;
};

TextQuery::TextQuery(ifstream& is): file(new vector<string>())
{
    // read line
    string text;
    cout << "building TextQuery" << endl;
    while(getline(is, text))
    {
        file->push_back(text);
        cout << text << endl;
        int n = file->size() - 1;
        istringstream line(text);
        string word;
        while(line >> word)
        {
            auto &lines = wm[word];
            if(!lines)
                lines.reset(new set<int>);
            lines->insert(n);
        }
    }
}

QueryResult TextQuery::Search(const string& s)
{
    static shared_ptr<set<int>> nodata(new set<int>);
    auto loc = wm.find(s);
    if(loc == wm.end())
        return QueryResult(s, nodata, file);
    else
        return QueryResult(s, loc->second, file);
}

void QueryResult::print()
{
    for(auto line : * lines)
        cout << line << ": " << (*file)[line] << endl;
}

#endif