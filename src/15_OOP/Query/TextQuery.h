#ifndef _TEXTQUERY_H_
#define _TEXTQUERY_H_
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <memory>
#include <set>
#include <map>
#include "StrVec.h"
#include "QueryResult.h"

class TextQuery{
public:
    using line_no = QueryResult::line_no;
    TextQuery(ifstream&);
    QueryResult Search(const string&) const;
private:
    shared_ptr<StrVec> file;
    map<string, shared_ptr<set<line_no>>> wm;
};

TextQuery::TextQuery(ifstream& is): file(new StrVec())
{
    // read line
    string text;
    cout << "building TextQuery" << endl;
    while(getline(is, text))
    {
        file->push_back(text);
        int n = file->size() - 1;
        istringstream line(text);
        string word;
        while(line >> word)
        {
            auto &lines = wm[word];
            if(!lines)
                lines.reset(new set<line_no>);
            lines->insert(n);
        }
    }
}

QueryResult TextQuery::Search(const string& s) const
{
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto loc = wm.find(s);
    if(loc == wm.end())
        return QueryResult(s, nodata, file);
    else
        return QueryResult(s, loc->second, file);
}

#endif