#pragma once

class Date
{
private:
	unsigned day = 1;
	unsigned month = 1;
	unsigned year = 2000;

	unsigned MONTHS[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	bool isLeap();
	unsigned getDays()
	{
		unsigned days = 0;
		days += day;
		
		for (size_t i = month - 2; i >= 0; i--)
		{
			days += MONTHS[i];
		}
	}
public:
	Date() = default;
	Date(unsigned day, unsigned month, unsigned year);

	void setDay(unsigned value);
	unsigned getDay() const;
	void setMonth(unsigned value);
	unsigned getMonth() const;
	void setYear(unsigned value);
	unsigned getYear() const;
};