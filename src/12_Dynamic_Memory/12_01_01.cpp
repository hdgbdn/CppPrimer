// shared_ptr & unique_ptr are difined in memory header
#include <memory>
#include <string>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

shared_ptr<string> factory(string s)
{
    return make_shared<string>(s);
}

class StrBlod{
public:
    typedef vector<string>::size_type size_type;
    StrBlod();
    StrBlod(initializer_list<string> il);
    size_type size() const {return data->size();}   // const member function: `this` pointer will be a pointer point to a const
                                                    // so the other function can not change the value returned
    bool empty() const {return data->empty();}
    void push_back(const string &t) {data->push_back(t);}
    void pop_back();
    int data_use_count() const {return data.use_count();};
    string& front();
    string& back();
private:            
    shared_ptr<vector<string>> data;
    void check(size_type i, const string &msg) const;
};

StrBlod::StrBlod() : data(make_shared<vector<string>>()) {}
StrBlod::StrBlod(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}

void StrBlod::check(size_type i, const string &msg) const
{
    if(i > data->size())
        throw out_of_range(msg);
}

// what to return if there are nothing to return? since the return type is reference?
// answer: throw out_of_range

string& StrBlod::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}

string& StrBlod::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlod::pop_back()
{
    check(0, "pop back on empty StrBlob");
    data->pop_back();
}

int main()
{
	{
		// smart pointers are template
		shared_ptr<string> p1;  // use defaut construction
		shared_ptr<list<int>> p2;

		// if p1 is not empty and the string p1 pointed to is empty
		// assign a new string
		// since p1 is a empty pointer, the "p1" if false
		if(p1 && p1->empty())
		{
			cout << "p1 is empty" << endl;
			*p1 = "hi";
		}

		// but we can point p1 to an empty string
		p1 = make_shared<string>();
		if (p1 && p1->empty())
		{
			cout << "p1 is empty after point to a make_shared" << endl;
			*p1 = "hi";
		}
	}

	// make_shared
	// works like: construct an object, then return the shared_ptr
	// note: if shared_ptr<base> p = make_shared<base>(derivedobj);
	// then you will only get a p point to a base obj, not a derived obj, because make_shared constructs a base obj.
	{
        shared_ptr<int> p3 = make_shared<int>(42);
        shared_ptr<string> p4 = make_shared<string>(10, '9');
        shared_ptr<int> p5 = make_shared<int>(); //value-initialized

        auto p6 = make_shared<vector<string>>();

        auto p = make_shared<int>(42);
        auto q(p);

        auto r = make_shared<int>(42);
        r = q;
	}

    // when use count == 0, shared_ptr will automatically free memory
	{
        auto p7 = factory("test");
        cout << "the use count of p7 is " << p7.use_count() << endl;
        // the use count of p7 is 1
		// after leaving the scope, p7 will be free
	}

	// why use dynamic allocate
	// 1: don't know the number of objects
	// 2: don't know the exact type(base derive)
	// 3: shared data

	{
        vector<string> v1;
        {
            vector<string> v2 = { "a", "an", "the" };
            v1 = v2;
        }
        cout << "v1 is a copy of v2" << endl;
        for (auto v : v1)
            cout << "v1: " << v << endl;
	}

    // vector owns the elements, it means the element in vector is separated from the origin one
	// but if we want to share the same elements between objects?

    // StrBlob
    StrBlod blod_a({"hi, hello"});
    cout << "the blod_a use count after construction is " << blod_a.data_use_count() << endl;               // 1
    StrBlod blod_b(blod_a);
    cout << "the blod_a use count after copy construction is " << blod_a.data_use_count() << endl;          // 2
    cout << "the blod_b use count by copy construction is " << blod_b.data_use_count() << endl;             // 2
    StrBlod blod_c = blod_b;
    cout << "the blod_a use count after assignment construction is " << blod_a.data_use_count() << endl;    // 3   
    cout << "the blod_b use count after assignment construction is " << blod_b.data_use_count() << endl;    // 3
    cout << "the blod_c use count by assignment construction is " << blod_c.data_use_count() << endl;       // 3
    const StrBlod& const_blod_d(blod_a);

    return 0;
}