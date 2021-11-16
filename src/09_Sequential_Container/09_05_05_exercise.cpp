#include "fmt/ranges.h"
#include <vector>
#include <string>
#include <random>
#include <functional>

using namespace std;
using namespace fmt;

class MyDate
{
public:
	MyDate(const string& date)
	{
		unsigned int format = 0x00;
		if (date.find_first_of(',') != string::npos)
			// January 1, 1990
			format = 0x01;
		else if (date.find_first_of('/') != string::npos)
			// 1/1/1900
			format = 0x10;
		else if (date.find_first_of(' ') == static_cast<string::size_type>(3))
			// Jan 1 1900
			format = 0x11;

		string yearStr, monStr, dayStr;
		string::size_type yearEndPos, monEndPos, dayEndPos;

		switch (format)
		{
		case 0x01:
			// January 1, 1990
			monEndPos = date.find_first_of(' ');
			monStr = date.substr(0, monEndPos);
			if (monStr == "January")	month = 1;
			if (monStr == "February")	month = 2;
			if (monStr == "March")		month = 3;
			if (monStr == "April")		month = 4;
			if (monStr == "May")		month = 5;
			if (monStr == "June")		month = 6;
			if (monStr == "July")		month = 7;
			if (monStr == "August")		month = 8;
			if (monStr == "September")	month = 9;
			if (monStr == "October")	month = 10;
			if (monStr == "November")	month = 11;
			if (monStr == "December")	month = 12;

			dayEndPos = date.find(',', monEndPos + 1);
			dayStr = date.substr(monEndPos + 1, dayEndPos - monEndPos + 1);
			day = stoi(dayStr);

			yearEndPos = date.find_last_of("0123456789");
			yearStr = date.substr(dayEndPos + 1, yearEndPos - dayEndPos + 1);
			year = stoi(yearStr);

			break;
		case 0x10:
			// 1/1/1900
			monEndPos = date.find_first_of('/');
			monStr = date.substr(0, monEndPos);
			month = stoi(monStr);

			dayEndPos = date.find_first_of('/', monEndPos + 1);
			dayStr = date.substr(monEndPos + 1, monEndPos);
			day = stoi(dayStr);

			yearEndPos = date.size() - 1;
			yearStr = date.substr(dayEndPos + 1, yearEndPos);
			year = stoi(yearStr);

			break;
		case 0x11:
			// Jan 1 1900
			monEndPos = date.find_first_of(' ');
			monStr = date.substr(0, monEndPos);

			if (monStr == "Jan") month = 1;
			if (monStr == "Feb") month = 2;
			if (monStr == "Mar") month = 3;
			if (monStr == "Apr") month = 4;
			if (monStr == "May") month = 5;
			if (monStr == "Jun") month = 6;
			if (monStr == "Jul") month = 7;
			if (monStr == "Aug") month = 8;
			if (monStr == "Sep") month = 9;
			if (monStr == "Oct") month = 10;
			if (monStr == "Nov") month = 11;
			if (monStr == "Dec") month = 12;

			dayEndPos = date.find_first_of(' ', monEndPos + 1);
			dayStr = date.substr(monEndPos + 1, monEndPos);
			day = stoi(dayStr);

			yearEndPos = date.size() - 1;
			yearStr = date.substr(dayEndPos + 1, yearEndPos);
			year = stoi(yearStr);
			break;
		}
	}
private:
	unsigned short int year, month, day;
};

int main()
{
	{
		// 9.50
		auto sumOfIntVec = [](const vector<string>& vec)->int
		{
			int ret = 0;
			for(auto s : vec)
			{
				ret += stoi(s);
			}
			return ret;
		};
		vector<string> iSvec = { "123", "111", "1234" };
		print("sum of integer string vector is {}\n", sumOfIntVec(iSvec));
		auto sumOfDoubleVec = [](const vector<string>& vec)->double
		{
			double ret = 0;
			for (auto s : vec)
			{
				ret += stod(s);
			}
			return ret;
		};
		vector<string> dSvec = { "1.23", "11.1", "1.234" };
		print("sum of float string vector is {}\n", sumOfDoubleVec(dSvec));
	}
	{
		// 9.51
		MyDate("Jan 1 1900");
	}
	return 0;
}
