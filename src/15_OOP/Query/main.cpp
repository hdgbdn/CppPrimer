#include <iostream>
#include <fstream>
#include <string>
#include "Query.h"
#include "NotQuery.h"
#include "AndQuery.h"
#include "OrQuery.h"
#include "TextQuery.h"

void eval(Query q, const TextQuery& t)
{
    cout << "Query: " << q.rep() << endl;
    cout << q.eval(t);
}

int main()
{
    ifstream file;
    file.open("text.txt");
    Query q1("Alice");
    TextQuery t(file);
    eval(q1, t);
    Query q2 = ~Query("Alice");
    eval(q2, t);
    Query q3 = Query("Alice") & Query("long");
    eval(q3, t);
    Query q4 = Query("Alice") | Query("is");
    eval(q4, t);
    return 0;
}