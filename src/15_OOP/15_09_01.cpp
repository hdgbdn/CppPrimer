#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

int main()
{
    // we want to search a text like: (fiery & bird | wind)
    // before we design a class: TextQuery, stores every word's occurs lines use map<string, shared_ptr<set<int>>>

    // based on the TextQuery, we want to add logic 'not', 'or' and 'and'
    // (fiery & bird | wind) is like line have fiery and bird or has wind

    // It's not a good idea to use TextQuery as a base class, because like 'not' operation, we have to find all the lines that
    // contains the complementary set of that word, a better way is to find all the line contains that word, and the reset lines match the 'not'

    // define a abs base class Query_base, and derive WordQuery and NotQuery, then derive abs class BinaryQuery as base of AndQuery and OrQuery
    // because the and or classes needs two parameters, differ from the WordQuery and NotQuer.

    // Query q = Query("fiery") & Query("bird") | Query("wind")
    // we use anther class 'Query" as interface.
    // user just need to konw the Query as interface, so Query contains a pointer to Query_base
    // so there are three WordQuery objects, and the & operator bind fiery and bird into a AndQuery object
    // and the | operator bind the AndQuery object and the WordQuery object into a OrQuery object
}