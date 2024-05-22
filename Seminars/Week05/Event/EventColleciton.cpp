#include "EventColleciton.h"
#include <iostream>

bool EventCollection::addEvent(const Event& event)
{
	if (count == 20)
	{
		return false;
	}

	events[count++] = event;
	return true;
}

bool EventCollection::removeEventByIndex(unsigned idx)
{
	if (idx >= count)
	{
		return false;
	}

	for (size_t i = idx; i < count - 1; i++)
	{
		events[idx] = events[idx + 1];
	}
	count--;
	return true;
}

bool EventCollection::removeEventByName(const char* name)
{
	if (!name)
	{
		return false;
	}

	int idx = getEventIndexByName(name);
	if (idx == -1)
	{
		return false;
	}

	return removeEventByIndex(idx);
}

int EventCollection::getEventIndexByName(const char* name) const
{
	if (!name)
	{
		return -1;
	}

	for (size_t i = 0; i < count; i++)
	{
		if (strcmp(events[i].getName(), name) == 0)
		{
			return i;
		}
	}
	return -1;
}

void EventCollection::print() const
{
	for (size_t i = 0; i < count; i++)
	{
		std::cout << events[i].getName() << std::endl;
	}
}

EventCollection EventCollection::getEventsOnDate(const BulgarianDate& date) const
{
	EventCollection eventsOnDate;

	for (size_t i = 0; i < count; i++)
	{
		if (compareBulgarianDates(date, events[i].getDate()) == 0)
		{
			eventsOnDate.addEvent(events[i]);
		}
	}

	return eventsOnDate;
}
