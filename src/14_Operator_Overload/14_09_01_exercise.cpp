#include <iostream>
#include <string>
#include <algorithm>
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

  operator string() const { return bookNo; }
  operator double() const { return revenue; }

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
    // 14.45
    // return bookNo and revenue
    Sales_data sd("Hello", 12345, 19.99);
    cout << static_cast<string>(sd) << endl;
    cout << static_cast<double>(sd) << endl;

    // 14.46
    // shoule be explicit, because if implicit, it will be some unexcpet behaviour like:
    // sd + 12.0, such meanless conversation

    // 14.48

    //
    return 0;
}