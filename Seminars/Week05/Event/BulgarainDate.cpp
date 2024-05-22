#include "BulgarainDate.h"
#include <iostream>

bool BulgarianDate::isLeapYear()
{
	if (year <= 1916)
	{
		return year % 4 == 0;
	}
	else
	{
		return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
	}
}
void BulgarianDate::validateDate()
{
	isDateInValidState = !((month == 0 || month > 12) ||
		(day == 0 || day > MAX_DAYS[month - 1]) ||
		(year == 0) ||
		(year == 1916 && month == 4 && day < 14));
}

BulgarianDate::BulgarianDate(unsigned day, unsigned month, unsigned year)
{
	setYear(year);
	setMonth(month);
	setDay(day);
}

void BulgarianDate::setDay(unsigned dVal)
{
	if (!good()) 
	{
		return;
	}
	day = dVal;
	isModified = true;
	validateDate();
}
unsigned BulgarianDate::getDay() const
{
	if (!good()) return 0;
	return day;
}

void BulgarianDate::setMonth(unsigned mVal)
{
	if (!good())
	{
		return;
	}
	month = mVal;
	isModified = true;
	validateDate();
}
unsigned BulgarianDate::getMonth() const
{
	if (!good()) return 0;
	return month;
}

void BulgarianDate::setYear(unsigned yVal)
{
	if (!good())
	{
		return;
	}
	year = yVal;
	if (isLeapYear())
	{
		MAX_DAYS[1] = 29;
	}
	else
	{
		MAX_DAYS[1] = 28;
	}

	isModified = true;
	validateDate();
}
unsigned BulgarianDate::getYear() const
{
	if (!good()) return 0;
	return year;
}

void BulgarianDate::print() const
{
	if (!good())
	{
		return;
	}
	std::cout << day << '.' << month << '.' << year << std::endl;
}

void BulgarianDate::goToNextDay()
{
	if (!good())
	{
		return;
	}

	if (year == 1916 && month == 3 && day == 31)
	{
		day = 14;
		month = 4;
	}
	else
	{
		day++;
		if (day > MAX_DAYS[month - 1])
		{
			setMonth(month == 12 ? 1 : (month + 1));
			if (month == 1)
			{
				setYear(year + 1);
			}
		}
	}
	isModified = true;
}

int BulgarianDate::getDayOfWeek() const
{
	if (!good())
	{
		return -1;
	}
	if (!isModified)
	{
		return dayOfWeek;
	}

	BulgarianDate d(1, 1, 1);
	int day = 5;

	while (compareBulgarianDates(d, *this) != 0)
	{
		d.goToNextDay();
		day++;
		day %= 7;
	}

	dayOfWeek = day + 1;
	isModified = false;
	return dayOfWeek;
}


bool BulgarianDate::good() const
{
	return isDateInValidState;
}

void BulgarianDate::clear()
{
	isDateInValidState = true;
	year = month = day = 1;
}

int compareBulgarianDates(const BulgarianDate& lhs, const BulgarianDate& rhs)
{
	if (lhs.getYear() < rhs.getYear())
	{
		return -1;
	}
	else if (lhs.getYear() > rhs.getYear())
	{
		return 1;
	}
	else
	{
		if (lhs.getMonth() < rhs.getMonth())
		{
			return -1;
		}
		else if (lhs.getMonth() > rhs.getMonth())
		{
			return 1;
		}
		else
		{
			if (lhs.getDay() < rhs.getDay())
			{
				return -1;
			}
			else if (lhs.getDay() > rhs.getDay())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	return 0;
}
