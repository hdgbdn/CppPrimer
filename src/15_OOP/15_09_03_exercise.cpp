#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <memory>

using namespace std;

class Query;

class Query_base{
    friend class Query;
protected:
    virtual ~Query_base() = default;
private:
    virtual string rep() const = 0;
};

class WordQuery : public Query_base {
    friend class Query;
    WordQuery(const string& s) : query_word(s) {}
    string rep() const override
    { return query_word; }
    string query_word;
};

class Query{
    friend Query operator~(const Query&);
    friend Query operator&(const Query&, const Query&);
    friend Query operator|(const Query&, const Query&);
public:
    Query(const string&);
    string rep() const
    { return q->rep(); }
private:
    Query(shared_ptr<Query_base> query): q(query) {}
    shared_ptr<Query_base> q;
};

Query::Query(const string& s): q(new WordQuery(s)) {}

class NotQuery: public Query_base{
    friend Query operator~(const Query&);
    NotQuery(const Query& q): query(q) {}
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
    BinaryQuery(const Query& l, const Query& r, string s): lhs(l), rhs(r), opSym(s) {}
    string rep() const override
    { return "("+lhs.rep()+" "+opSym+" "+rhs.rep()+")"; }
    Query lhs, rhs;
    string opSym;
};

class AndQuery: public BinaryQuery{
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query& left, const Query& right): BinaryQuery(left, right, "&") {}
};
inline
Query operator&(const Query& lhs, const Query& rhs){
    return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

class OrQuery: public BinaryQuery{
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query& left, const Query& right): BinaryQuery(left, right, "|") {}
};
inline
Query operator|(const Query& lhs, const Query& rhs){
    return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

ostream& operator<<(ostream& os, const Query& query){
    return os << query.rep();
}

int main()
{
    // 15.34
    // Query q = Query("fiery") & Query("bird") | Query("wind");
    // Query("fiery") creates a WordQuery and a Query, same as Query("bird") Query("wind")
    // operator & creates an Query and a AndQuery
    // operator | creates an Query and an OrQuery
    // finaly the lvalue q

    // cout << q;
    // the q's pointer is point to an OrQuery
    
    // q.eval()
    // the q's pointer is point to an OrQuery

    // 15.35
    Query q = Query("fiery") & Query("bird") | Query("wind");
    cout << q;
    return 0;
}