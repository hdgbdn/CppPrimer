#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <string>
#include <set>

using namespace std;

class Message{
    friend class Folder;
    friend void swap(Message&, Message&);
public:
    explicit Message(const string& str = ""): contents(str) {}
    Message(const Message&);
    Message(Message &&m);
    Message& operator=(const Message&);
    Message& operator=(Message&&);
    ~Message();

    void save(Folder &);
    void remove(Folder &);
    void addFold(Folder*);
    void remFold(Folder*);
    void move_Folders(Message *m);
    void Print();
private:
    string contents;
    set<Folder*> folders;
    void add_to_Folders(const Message&);
    void remove_from_Folders();
};


class Folder{
    friend class Message;
public:
    explicit Folder(const string& str = "new floder"):name(str), messages(){};
    Folder(const Folder&);
    Folder& operator=(const Folder&);
    ~Folder();
    void addMsg(Message* msg);
    void remMsg(Message* msg);
    void Print();
private:
    void sync_messages(const Folder&);
    string name;
    set<Message*> messages;
};

void Message::save(Folder &f)
{
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder &f)
{
    folders.erase(&f);
    f.remMsg(this);
}

void Message::addFold(Folder* f)
{
    folders.insert(f);
}

void Message::remFold(Folder* f)
{
    folders.erase(f);
}

void Message::add_to_Folders(const Message& msg)
{
    for(auto f : msg.folders)
        f->addMsg(this);
}

void Message::remove_from_Folders()
{
    for(auto f : folders)
        f->remMsg(this);
}

Message::Message(const Message &msg): contents(msg.contents), folders(msg.folders)
{
    add_to_Folders(msg);
}

Message& Message::operator=(const Message& rhs)
{
    remove_from_Folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_Folders(*this);
    return *this;
}

Message::~Message()
{
    //remove_from_Folders();
}

void Message::Print()
{
    cout << "Message: " << contents << " in folders: ";
    for(auto f : folders)
        cout << f->name << " ";
    cout << endl;
}

// not just swap data member
// also update floders!
void swap(Message& lhs, Message& rhs)
{
    using std::swap;
    for(auto f : lhs.folders){
        f->remMsg(&lhs);
    }
    for(auto f : rhs.folders){
        f->remMsg(&rhs);
    }
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    for(auto f : lhs.folders){
        f->addMsg(&lhs);
    }
    for(auto f : rhs.folders){
        f->addMsg(&rhs);
    }
}

// move the set<Folder>
void Message::move_Folders(Message* m){
    folders = std::move(m->folders);
    for(auto f : folders){
        f->remMsg(m);
        f->addMsg(this);
    }
    // after move, the origin object is valid but unknown, so doing some clear for upcoming destructor
    m->folders.clear();
}

// move constructor
Message::Message(Message &&m): contents(std::move(m.contents)){
    cout << "Message class: move constructor" << endl;
    move_Folders(&m);
}

// move assignment
Message& Message::operator=(Message &&rhs){
    cout << "Message class: move assignment" << endl;
    if(this != &rhs){
        remove_from_Folders();
        contents = std::move(rhs.contents);
        move_Folders(&rhs);
    }
    return *this;
}

//------------------------- folder

Folder::Folder(const Folder& f)
{
    name = f.name;
    sync_messages(f);
}

Folder& Folder::operator=(const Folder& f)
{
    cout << "copying folder " << f.name << " to " << name << endl;
    name = f.name;
    sync_messages(f);
    return *this;
}

void Folder::addMsg(Message* msg)
{
    messages.insert(msg);
}

void Folder::remMsg(Message* msg)
{
    messages.erase(msg);
}

void Folder::sync_messages(const Folder& f)
{
    for(auto m : messages)
        m->remFold(this);

    messages = f.messages;
    for(auto m : messages)
        m->addFold(this);
}

Folder::~Folder()
{
    cout << "deleting folder " << name;
    for(auto m : messages)
        m->remFold(this);
}

void Folder::Print()
{
    cout << "Folder: " << name << " messages are ";
    for(auto m : messages)
        cout << m->contents << " ";
    cout << endl;
}

#endif