#ifndef _BINARYQUERY_H_
#define _BINARYQUERY_H_

#include "Query.h"
#include "Query_base.h"

class BinaryQuery : public Query_base{
protected:
	BinaryQuery(const Query& l, const Query& r, const string s): lhs(l), rhs(r), opSym(s){}
	string rep() const override
	{
		return ("("+lhs.rep()+" "+ opSym + " " + rhs.rep() + ")");
	}
	
	Query lhs;
	Query rhs;
	string opSym;
};

#endif