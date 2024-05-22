#pragma once

class BulgarianDate
{
private:
	unsigned MAX_DAYS[12] =
	{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	unsigned day = 1;
	unsigned month = 1;
	unsigned year = 1;

	bool isDateInValidState = true;
	mutable bool isModified = true;
	mutable int dayOfWeek = -1;

	bool isLeapYear();
	void validateDate();
public:
	BulgarianDate() = default;
	BulgarianDate(unsigned day, unsigned month, unsigned year);

	void setDay(unsigned dVal);
	unsigned getDay() const;

	void setMonth(unsigned mVal);
	unsigned getMonth() const;

	void setYear(unsigned yVal);
	unsigned getYear() const;

	void print() const;
	void goToNextDay();
	int getDayOfWeek() const;

	bool good() const;
	void clear();
};

int compareBulgarianDates(const BulgarianDate& lhs, const BulgarianDate& rhs);