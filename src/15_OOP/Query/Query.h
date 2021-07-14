#ifndef _QUERY_H_
#define _QUERY_H_

#include "QueryResult.h"
#include "Query_base.h"
#include "WordQuery.h"
#include "TextQuery.h"

class Query{
    friend Query operator~(const Query&);
    friend Query operator&(const Query&, const Query&);
    friend Query operator|(const Query&, const Query&);
public:
    Query(const string& s): q(new WordQuery(s)) {};
    QueryResult eval(const TextQuery& t) const { return q->eval(t); }
    string rep() const { return q->rep(); }
private:
    Query(shared_ptr<Query_base> query): q(query) {}
    shared_ptr<Query_base> q;
};

#endif