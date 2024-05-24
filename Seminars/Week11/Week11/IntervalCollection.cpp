#include "IntervalCollection.h"
#include "Utils.h"

IntervalCollection::IntervalCollection(int start, int end) 
{
	if (end < start)
	{
		std::swap(start, end);
	}

	this->start = start;
	this->end = end;

	int intervalSize = end - start + 1;
	data = new int[intervalSize] {0};
}

unsigned IntervalCollection::intervalLength() const
{
	return end - start + 1;
}

void IntervalCollection::add(int elem)
{
	if (elem < start || elem > end)
	{
		throw std::out_of_range("IntervalCollection::add(int elem); elem was out of interval range!");
	}

	int index = elem - start;
	data[index]++;
}

void IntervalCollection::remove(int elem)
{
	if (elem < start || elem > end)
	{
		throw std::out_of_range("IntervalCollection::remove(int elem); elem was out of interval range!");
	}

	int index = elem - start;
	if (data[index] == 0)
	{
		return;
	}

	data[index]--;
}

unsigned IntervalCollection::count(int elem) const
{
	if (elem < start || elem > end)
	{
		throw std::out_of_range("IntervalCollection::count(int elem); elem was out of interval range!");
	}

	int index = elem - start;
	return data[index];
}

bool IntervalCollection::contains(int elem) const
{
	return count(elem) > 0;
}
