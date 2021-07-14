#ifndef _QUERY_BASE_H_
#define _QUERY_BASE_H_

#include <iostream>
#include <string>
#include "QueryResult.h"
#include "TextQuery.h"

using namespace std;

class Query_base{
    friend class Query;
protected:
    using line_no = QueryResult::line_no;
    virtual ~Query_base() = default;
private:
    virtual QueryResult eval(const TextQuery&) const = 0;
    virtual string rep() const = 0;
};

#endif