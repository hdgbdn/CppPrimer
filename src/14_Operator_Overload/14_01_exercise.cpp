#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Sales_data;
std::istream &read(std::istream &, Sales_data &);

class Sales_data {
  friend Sales_data add(const Sales_data &, const Sales_data &);
  friend std::istream &read(std::istream &, Sales_data &);
  friend std::ostream &print(std::ostream &, const Sales_data &);
  friend std::istream &operator>>(std::istream &, Sales_data &);
  friend std::ostream &operator<<(std::ostream &, const Sales_data &);

public:
  Sales_data(const std::string &no = "", unsigned us = 0, double price = 0.0)
      : bookNo(no), units_sold(us), revenue(price * us) {}
  explicit Sales_data(const std::string &no) : Sales_data(no, 0, 0.0) {}
  explicit Sales_data(std::istream &is) : Sales_data() { read(is, *this); }

  Sales_data &operator+=(const Sales_data &);

  std::string isbn() const { return bookNo; }
  Sales_data &combine(const Sales_data &);

private:
  double avg_price() const;
  std::string bookNo;
  unsigned units_sold = 0;
  double revenue = 0.0;
};

Sales_data operator+(const Sales_data & lhs, const Sales_data & rhs)
{
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

Sales_data& Sales_data::operator+=(const Sales_data & rhs){
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

std::istream &operator>>(std::istream & is, Sales_data & item)
{
    double price;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = item.units_sold * price;
    return is;
}

std::ostream &operator<<(std::ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

inline
double Sales_data::avg_price() const {
  return units_sold ? revenue / units_sold : 0;
}

Sales_data &Sales_data::combine(const Sales_data &rhs) {
  units_sold += rhs.units_sold;
  revenue += rhs.revenue;
  return *this;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {
  Sales_data sum = lhs;
  sum.combine(rhs);
  return sum;
}

std::istream &read(std::istream &is, Sales_data &item) {
  double price;
  is >> item.bookNo >> item.units_sold >> price;
  item.revenue = item.units_sold * price;
  return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item) {
  os << item.isbn() << " " << item.units_sold << " "
     << item.revenue << " " << item.avg_price();
  return os;
}

bool compareIsbn(const Sales_data &sd1, const Sales_data &sd2) {
  return sd1.isbn() < sd2.isbn();
}

int main()
{
    // 14.1
    // differences:
    // overloaded: can be called like operator+(lhs, rhs); and don't have order of evaluation and/or short-circuit evaluation
    // same:
    // snytactically.

    // 14.2
    Sales_data item1("10086", 2000, 80);
    Sales_data item2("10000", 1000, 40);
    Sales_data item3 = item1 + item2;
    item1 += item2;
    cout << item1 << endl;
    cout << item2 << endl;
    cout << item3 << endl;
    cin >> item1;
    cout << item1 << endl;

    // 14.3
    "cobble" == "stone";        // build-in operator
    vector<string> svec1 = {"cobble1", "stone1"};
    vector<string> svec2 = {"cobble2", "stone2"};

    svec1[0] == svec2[0];       // overloaded string
    svec1 == svec2;             // overloaded vector
    // "svec1[0] == "stone";    // ?

    // 14.4
    // %: lhs and rhs can be swaped, non member
    // %=: changes itself, member
    // ++: changes itself, member
    // ->: use self data member, member
    // <<: operator left is stream, non member
    // &&: lhs and rhs can be swaped, non member
    // ==:  lhs and rhs can be swaped, non member
    // (): use self data member, member

    // 14.5
    // Book: like
    // Date: like ++, change itself
    // Employee: 
    // Vehicle:
    // Object:
    // Tree:

    return 0;
}