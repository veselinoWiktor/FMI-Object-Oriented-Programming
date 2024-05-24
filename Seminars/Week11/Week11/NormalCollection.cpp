#include "NormalCollection.h"

void NormalCollection::add(int elem)
{
	if (size == capacity)
	{
		resize(capacity * 2);
	}

	data[size++] = elem;
}

void NormalCollection::remove(int elem)
{
	int elemIndex = -1;

	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == elem)
		{
			elemIndex = i;
			break;
		}
	}

	if (elemIndex != -1)
	{
		std::swap(data[elemIndex], data[size - 1]);
		size--;
	}
}

unsigned NormalCollection::count(int elem) const
{
	unsigned counter = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == elem)
		{
			counter++;
		}
	}

	return counter;
}

bool NormalCollection::contains(int elem) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == elem)
		{
			return true;
		}
	}
	return false;
}
