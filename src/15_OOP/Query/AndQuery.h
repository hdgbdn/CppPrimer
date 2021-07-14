#ifndef _ANDQUERY_H_
#define _ANDQUERY_H_

#include "BinaryQuery.h"

class AndQuery: public BinaryQuery
{
	friend Query operator&(const Query&, const Query&);
	AndQuery(const Query& l, const Query& r) : BinaryQuery(l, r, "&") {}
	QueryResult eval(const TextQuery&) const override;
};

Query operator&(const Query& lhs, const Query& rhs)
{
	return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

inline QueryResult AndQuery::eval(const TextQuery& t) const
{
	auto ret = make_shared<set<line_no>>();
	auto lresult = lhs.eval(t);
	auto rresult = rhs.eval(t);
	auto lbeg = lresult.begin(), lend = lresult.end();
	auto rbeg = rresult.begin(), rend = rresult.end();
	auto lp = lbeg, rp = rbeg;
	while(lp != lend || rp != rend)
	{
		if (*lp == *rp)
		{
			ret->insert(*lp);
			++lp; ++rp;
		} 
		else
		{
			if (*lp < *rp) ++lp;
			else ++rp;
		}
	}
	return QueryResult(rep(), ret, lresult.get_file());
}

#endif