#ifndef _ORQUERY_H_
#define _ORQUERY_H_

#include "BinaryQuery.h"

class OrQuery: public BinaryQuery
{
	friend Query operator|(const Query&, const Query&);
	OrQuery(const Query& l, const Query& r) : BinaryQuery(l, r, "|") {}
	QueryResult eval(const TextQuery&) const override;
};

Query operator|(const Query& l, const Query& r)
{
	return shared_ptr<Query_base>(new OrQuery(l, r));
}

QueryResult OrQuery::eval(const TextQuery& t) const
{
	auto lresult = lhs.eval(t), rresult = rhs.eval(t);
	auto retlines = make_shared<set<line_no>>(lresult.begin(), lresult.end());
	retlines->insert(rresult.begin(), rresult.end());
	return QueryResult(rep(), retlines, lresult.get_file());
}


#endif