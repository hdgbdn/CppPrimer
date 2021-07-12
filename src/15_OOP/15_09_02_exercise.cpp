#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>
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
    for(auto line : *lines)
        cout << line << ": " << (*file)[line] << endl;
}

class Query;

class Query_base{
    friend class Query;
protected:
    virtual ~Query_base() = default;
private:
    virtual QueryResult eval(const TextQuery&) const = 0;
    virtual string rep() const = 0;
};

class Query{
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    Query(const string&);
    QueryResult eval(const TextQuery& t) const
        { return q->eval(t); }
    string rep() const
        { return q->rep(); }
private:
    Query(shared_ptr<Query_base> query): q(query) {}
    shared_ptr<Query_base> q;
};

ostream& operator<<(ostream& os, const Query& query){
    return os << query.rep();
}

int main()
{
    // 15.32
    // copy: since Query don't define copy constructor, it will have a synthesized one, the shared_ptr will be copied

    // move: since Query don't define user copy operations, so it will have a synthesized move operation. the pointer itself
    // will be moved.
    
    // assign: the shared_ptr will point to another, if the referenc count = 0, then the object pointed to will be destoried

    // destory: the shared_ptr will be sestroied, if there are no other pointer point to the object, the object will be destroied

    // 15.33
    // the Query_base is an abs base class, it can't create object;

    return 0;
}