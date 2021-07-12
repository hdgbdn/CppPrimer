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
    QueryResult Search(const string&) const;
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

QueryResult TextQuery::Search(const string& s) const
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

class WordQuery : public Query_base {
    friend class Query;
    WordQuery(const string& s) : query_word(s) {}
    QueryResult eval(const TextQuery& t) const override
    {
        return t.Search(query_word);
    }
    string rep() const override
    {
        return query_word;
    }
    string query_word;
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

inline
Query::Query(const string& s): q(new WordQuery(s)){}

ostream& operator<<(ostream& os, const Query& query){
    return os << query.rep();
}

class NotQuery: public Query_base{
    friend Query operator~(const Query&);
    NotQuery(const Query& q): query(q) {}
    QueryResult eval(const TextQuery& t) const override;
    string rep() const override
        { return "~("+query.rep()+")"; }
    Query query;
};

inline 
Query operator~(const Query& operand){
    return shared_ptr<Query_base>(new NotQuery(operand));
}

class BinaryQuery: public Query_base{
protected:
    BinaryQuery(const Query& l, const Query& r, string s);

    string rep() const override
    { return "("+lhs.rep()+" "+opSym+" "+rhs.rep()+")"; }
    Query lhs, rhs;
    string opSym;
};

class AndQuery: public BinaryQuery{
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query& left, const Query& right): BinaryQuery(left, right, "&") {}
    QueryResult eval(const TextQuery& t) const override;
};
inline Query operator&(const Query& lhs, const Query& rhs){
    return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

class OrQuery: public BinaryQuery{
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query& left, const Query& right): BinaryQuery(left, right, "|") {}
    QueryResult eval(const TextQuery& t) const override;
};
inline Query operator|(const Query& lhs, const Query& rhs){
    return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

int main()
{
    return 0;
}