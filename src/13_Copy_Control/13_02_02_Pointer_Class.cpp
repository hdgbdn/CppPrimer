#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

class HasPtr{
public:
    HasPtr(const string &s = string());
    HasPtr(const HasPtr&);
    HasPtr& operator=(const HasPtr&);
    ~HasPtr();
    void Print();
private:
    int i;
    string* ps;
    size_t* pcount;
};

HasPtr::HasPtr(const string &s) : ps(new string(s)), i(0), pcount(new size_t(1)) {
    cout << "constructing " << *ps << " use count is " << *pcount << endl;
}

HasPtr::HasPtr(const HasPtr &ptr) : ps(ptr.ps), i(ptr.i), pcount(ptr.pcount) {
    ++(*pcount);
    cout << "copy constructing " << *ps << " use count is " << *pcount << endl;
}

HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
    ++(*rhs.pcount);
    if(--*pcount == 0){
        cout << "deleting " << *ps << " because assing new value, and use count have decreased to 0"<< endl;
        delete ps;
        delete pcount;
    }
    pcount = rhs.pcount;
    ps = rhs.ps;
    i = rhs.i;
    cout << "copy assigning " << *ps << " use count is " << *pcount << endl;
    return *this;
}

HasPtr::~HasPtr()
{
    if(--*pcount == 0){
        cout << "use count of " << *ps << " have decreased to 0, free memory" << endl;
        delete ps;
        delete pcount;
    }
}

class TreeNode{
public:
    TreeNode(string s = string());
    TreeNode(const TreeNode&);
    TreeNode& operator=(const TreeNode&);
    ~TreeNode();
private:
    string      value;
    int         count;
    TreeNode*   left;
    TreeNode*   right;
};

TreeNode::TreeNode(string s): value(s), count(0), left(nullptr), right(nullptr){ }

TreeNode::TreeNode(const TreeNode& node): value(node.value), count(node.count) {
    if(node.left)
        left = new TreeNode(*(node.left));
    if(node.right)
        right = new TreeNode(*(node.right));
}

TreeNode& TreeNode::operator=(const TreeNode& node){
    value = node.value;
    count = node.count;
    delete left;
    delete right;
    left = new TreeNode(*node.left);
    right = new TreeNode(*node.right);
};

TreeNode::~TreeNode(){
    delete left;
    delete right;
}

class BinStrTree{
    BinStrTree();
    BinStrTree(const BinStrTree&);
    BinStrTree& operator=(const BinStrTree&);
private:
    TreeNode *root;
};

BinStrTree::BinStrTree(): root(nullptr){ }

BinStrTree::BinStrTree(const BinStrTree& bt): root(new TreeNode(*bt.root)){
    
}

int main()
{
    HasPtr p1("hello");
    HasPtr p2(p1);
    {
        HasPtr p3("p3");
    }
    HasPtr p4("p4");
    p4 = p2;
    return 0;
}