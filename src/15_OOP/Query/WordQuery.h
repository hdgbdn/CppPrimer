#ifndef _WORDQUERY_H_
#define _WORDQUERY_H_

#include "Query_base.h"
#include "QueryResult.h"
#include "TextQuery.h"

class WordQuery: public Query_base{
    friend class Query;
    WordQuery(const string& s): query_word(s) {}
    QueryResult eval(const TextQuery& t) const override{
        return t.Search(query_word);
    }   
    string rep() const { return query_word; }
    string query_word;
};

#endif