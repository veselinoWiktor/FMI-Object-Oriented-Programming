#include "Date.h"

bool Date::isLeap()
{
	return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

Date::Date(unsigned day, unsigned month, unsigned year)
{
	setYear(year);
	setMonth(month);
	setDay(day);
}

void Date::setDay(unsigned value)
{
	if (value > MONTHS[month - 1])
	{
		day = 1;
	}
	else
	{
		day = value;
	}
}

unsigned Date::getDay() const
{
	return day;
}

void Date::setMonth(unsigned value)
{
	if (month > 12)
	{
		month = 1;
	}
	else
	{
		month = value;
	}
}

unsigned Date::getMonth() const
{
	return month;
}

void Date::setYear(unsigned value)
{
	if (year > 9999)
	{
		year = 2000;
	}
	else
	{
		year = value;
	}

	MONTHS[1] = isLeap() ? 29 : 28;
}

unsigned Date::getYear() const
{
	return year;
}
