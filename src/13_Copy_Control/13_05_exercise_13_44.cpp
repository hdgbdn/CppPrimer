#include <iostream>
#include <string>
#include <utility>
#include <memory>
#include <functional>
#include <algorithm>

using namespace std;

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
	auto data = alloc_n_copy(c, c + strlen(c) + 1);
	elements = data.first;
	first_free = cap = data.second;
}

MyString::MyString(const MyString& ms)
{
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
	MyString s1;
	s1.Print();
	MyString s2("s2");
	s2.Print();
	MyString s3(s2);
	s3.Print();
	s2.push_back('p');
	s2.Print();
	s2.pop_back();
	s2.Print();

    string realstr;
    cout << realstr << endl;
    realstr.push_back('\0');
    cout << realstr << endl;
    realstr.push_back('a');
    cout << realstr << endl;
}