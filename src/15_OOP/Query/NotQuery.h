#ifndef _NOTQUERY_H_
#define _NOTQUERY_H_

#include "Query.h"
#include "Query_base.h"

class NotQuery : public Query_base{
	friend Query operator~(const Query&);
	NotQuery(const Query& q): query(q){}
	string rep() const override
	{
		return "~" + query.rep();
	}
	QueryResult eval(const TextQuery& t) const override
	{
		auto result = query.eval(t);
		auto retlines = make_shared<set<line_no>>();
		auto file = result.get_file();
		auto sz = file->size();
		auto beg = result.begin(), end = result.end();
		for(size_t n = 0; n < sz; ++n)
		{
			if (beg == end || *beg != n)
				retlines->insert(n);
			else if (beg != end) ++beg;
		}
		return QueryResult(rep(), retlines, file);
	}
	Query query;
};

Query operator~(const Query& operand)
{
	return shared_ptr<Query_base>(new NotQuery(operand));
}

#endif