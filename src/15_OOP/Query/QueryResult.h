#ifndef _QUERYRESULT_H_
#define _QUERYRESULT_H_

#include <string>
#include <memory>
#include <set>
#include "StrVec.h"

class QueryResult{
    friend ostream& operator<<(ostream&, const QueryResult&);
public:
    using line_no = size_t;
    QueryResult(string s, shared_ptr<set<line_no>> l, shared_ptr<StrVec> f): s(s), lines(l), file(f) {};
    shared_ptr<StrVec> get_file() { return file; }
    auto begin() { return lines->begin(); }
    auto end() { return lines->end(); }
    void print();
private:
    string s;
    shared_ptr<set<line_no>> lines;
    shared_ptr<StrVec> file;
};

ostream& operator<<(ostream& os, const QueryResult& qr)
{
	if ((*qr.lines).size() == 0)
	{
		os << "empty result" << endl;
	}
	else
	{
		for (auto line : *qr.lines)
		{
			os << line << ": " << (*qr.file)[line] << endl;
		}

	}
	return os;
}

void QueryResult::print()
{
    for (auto line : *lines)
        cout << line << ": " << (*file)[line] << endl;
}

#endif