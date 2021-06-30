#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class HasPtr
{
    friend void swap(HasPtr &, HasPtr &);
public:
    HasPtr(const string &s = string()) : ps(new string(s)), i(0) {cout << "HasPtr default constructor" << endl;}
    HasPtr(HasPtr&& p) noexcept: ps(p.ps), i(p.i) {p.ps = nullptr; cout << "HasPtr move constructor" << endl;}
    HasPtr(const HasPtr &ptr) : ps(new string(*ptr.ps)), i(ptr.i) {cout << "HasPtr copy constructor" << endl;}
    //HasPtr& operator=(HasPtr rhs){cout << "HasPtr copy&swap assignment" << endl; swap(*this, rhs); return *this; }
	HasPtr& operator=(const HasPtr& rhs);
	HasPtr& operator=(HasPtr&&);
    ~HasPtr() { delete ps; }

private:
    string *ps;
    int i;
};

inline
void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}

HasPtr& HasPtr::operator=(const HasPtr& rhs){
	cout << "const reference version assignment" << endl;
	if(&rhs != this)
	{
		delete this->ps;
		this->ps = new string(*rhs.ps);
		this->i = rhs.i;
	}
	return *this;
}

HasPtr& HasPtr::operator=(HasPtr&& rhs){
	cout << "rvalue reference version assignment" << endl;
	this->ps = rhs.ps;
	this->i = rhs.i;
	rhs.ps = nullptr;
	return *this;
}

int main()
{
    // 13.51
	auto clone = [](int p)->unique_ptr<int>{
		return unique_ptr<int> (new int(p));
	};
	// because the returned value is an rvalue reference, it's moved not copied

	// 13.52
	HasPtr hp, hp2;			// use default constructor to construct 2 objects
	hp = hp2;				// hp2 directly copied into '=' operator's parameter
	hp = std::move(hp2);	// hp2 is rvalue, so use move constructor to construct an lvalue, and pass the lvalue to '=' operator's parameter
	// so hp, hp2: HasPtr default constructor * 2
	// hp2 = hp: hp copied to construct rhs, then copy assign
	// hp = std::move(hp2): the rvlaue std::move returned, will move construct the rhs, the copy assign

	// 13.53
	// because for lvalue, it copy construct a new object, and for rvalue, it move construct a new values
	// see HasPtr& operator=(const HasPtr& rhs);HasPtr& operator=(HasPtr&&);
	// don't construct any new objects

	// 13.54
	// more than one operator "=" matches these operands:
	
	return 0;
}