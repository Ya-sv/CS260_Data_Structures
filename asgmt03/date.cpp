#include "date.h"

using namespace std;

Date::Date(Month month, int day, int year):

	month { month },
	day { day },
	year { year }

{
	
}


Date::Date():
	month{ INVALID },
	day{ 0 },
	year{0}
{

}


Date::~Date(void)
{
	// No pointer data to delete
}

ostream& operator<<(ostream& out, const Date& d)
{
	switch (d.month)
	{
		case Date::Month::JANUARY:
			out << "January ";
			break;
		case Date::Month::FEBRUARY:
			out << "February " ;
			break;
		case Date::Month::MARCH:
			out << "March ";
			break;
		case Date::Month::APRIL:
			out << "April ";
			break;
		case Date::Month::MAY:
			out << "May ";
			break;
		case Date::Month::JUNE:
			out << "June ";
			break;
		case Date::Month::JULY:
			out << "July ";
			break;
		case Date::Month::AUGUST:
			out << "August ";
			break;
		case Date::Month::SEPTEMBER:
			out << "September ";
			break;
		case Date::Month::OCTOBER:
			out << "October " ;
			break;
		case Date::Month::NOVEMBER:
			out << "November ";
			break;
		case Date::Month::DECEMBER:
			out << "December ";
			break;

		default:
			out << "INVALID ";
			break;
	}
	out << d.day << ", " << d.year << endl;
	return out;
}
