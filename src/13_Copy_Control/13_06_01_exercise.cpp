#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

int f(){
    return 1;
}

class MyString
{
public:
	MyString(): elements(nullptr), first_free(nullptr), cap(nullptr) {}
	MyString(const char*);
	MyString(const MyString&);
	~MyString();
	char& operator[](size_t);
	void pop_back();
	void push_back(const char&);
	MyString operator=(const MyString&);
	char* begin();
	char* end();
	const char* cbegin() const;
	const char* cend() const;
	void empty();
	size_t size() { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	void Print();
private:
	static allocator<char> alloc;
	void chk_n_alloc() { if (size() == capacity()) reallocate(size() ? 2 * size() : 1); }
	pair<char*, char*> alloc_n_copy(const char*, const char*);
	void reallocate(size_t n);
	void free();
	char* elements;
	char* first_free;
	char* cap;
};

pair<char*, char*> MyString::alloc_n_copy(const char* b, const char* e)
{
	auto data = alloc.allocate(e - b);
	return { data, uninitialized_copy(b, e, data) };
}

MyString::MyString(const char* c): elements(nullptr), first_free(nullptr), cap(nullptr)
{
    cout << "default constructor, content is " << c << endl;
	auto data = alloc_n_copy(c, c + strlen(c) + 1);
	elements = data.first;
	first_free = cap = data.second;
}

MyString::MyString(const MyString& ms)
{
    cout << "copy constructor, content is " << ms.elements << endl;
	auto data = alloc_n_copy(ms.cbegin(), ms.cend());
	elements = data.first;
	first_free = cap = data.second;
}

MyString::~MyString()
{
	free();
}

const char* MyString::cbegin() const
{
	return elements;
}

const char* MyString::cend() const
{
	return first_free;
}

char* MyString::begin()
{
	return
		const_cast<char*>(
			this->cbegin()
			);
}

char* MyString::end()
{
	return
		const_cast<char*>(
			this->cend()
			);
}

void MyString::reallocate(size_t n)
{
	auto newcapacity = n;
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	auto elem = elements;
	for (size_t i = 0; i != size(); ++i)
	{
		if (i >= n) break;
		alloc.construct(dest++, std::move(*elem++));
	}
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}

void MyString::free()
{
	if (elements == nullptr) return;
	for (auto p = first_free; p != elements; )
		alloc.destroy(--p);
	alloc.deallocate(elements, cap - elements);
}

void MyString::pop_back()
{
	if (elements == first_free) return;
	if (*(first_free-1) == '\0')
	{
		alloc.destroy(--first_free);
		alloc.construct(first_free - 1, '\0');
	}
	
}

void MyString::push_back(const char& c)
{
	chk_n_alloc();
	alloc.construct(first_free - 1, c);
	alloc.construct(first_free++, '\0');
}

void MyString::Print()
{
	if (elements == nullptr) cout << "empty MyString" << endl;
	else cout << "content is " << elements << " size is " << size() << " cap is " << capacity() << endl;
}


allocator<char> MyString::alloc;

int main()
{
    // 13.45
    // rvalue reference is reference bound to rvalue
    
    // 13.46
    int f();                // f is a name, so lvalue
    vector<int> vi(100);    // vi is a name, so lvalue;
    int&& r1 = f();         // f return a temp value;
    int& r2 = vi[0];        // vi[0] is a non temp value;
    int &r3 = r1;           // r1 now is a non temp value;
    int&& r4 = vi[0] * f(); // vi[0] * f() is a temp value;

    // 13.47
    // 13.48
    vector<MyString> v;
    v.push_back("hi");
    v.push_back("hello");
    // default constructor, content is hi
    // copy constructor, content is hi
    // default constructor, content is hello
    // copy constructor, content is hello
    // copy constructor, content is hi
}