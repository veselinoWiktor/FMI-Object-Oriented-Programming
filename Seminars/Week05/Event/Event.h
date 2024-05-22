#pragma once
#include "BulgarainDate.h"
#include "Time.h"

class Event
{
private:
	char name[20 + 1];
	BulgarianDate date;
	Time startTime;
	Time endTime;

	void validateTime();

public:
	Event();
	Event(const char* _name, const BulgarianDate& _date, const Time& _startTime, const Time& _endTime);
	Event(const char* _name, unsigned day, unsigned month, unsigned year,
		unsigned startHour, unsigned startMinutes, unsigned startSeconds,
		unsigned endHour, unsigned endMinutes, unsigned endSeconds);

	void setName(const char* _name);
	const char* getName() const;
	const BulgarianDate& getDate() const;
	const Time& getStartTime() const;
	const Time& getEndTime() const;
};