#include "SortedCollection.h"

int SortedCollection::lowerBound(int x) const
{
	int left = 0;
	int right = size - 1;

	int indexToReturn = size;

	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (data[mid] < x)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
			indexToReturn = mid;
		}
	}

	return indexToReturn;
}

int SortedCollection::upperBound(int x) const
{
	int left = 0;
	int right = size - 1;
	 
	int indexToReturn = size;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (data[mid] <= x)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
			indexToReturn = mid;
		}
	}

	return indexToReturn;
}

void SortedCollection::add(int elem)
{
	if (size == capacity)
	{
		resize(capacity * 2);
	}

	int idx = size;

	while (idx != 0 && data[idx - 1] > elem)
	{
		data[idx] = data[idx - 1];
		--idx;
	}

	data[idx] = elem;
	++size;
}

void SortedCollection::remove(int elem)
{
	int elementIndex = lowerBound(elem);

	if (elementIndex == size)
	{
		return;
	}

	for (size_t i = elementIndex; i < size - 1; i++)
	{
		data[i] = data[i + 1];
	}

	--size;
}

unsigned SortedCollection::count(int elem) const
{
	int leftIndex = lowerBound(elem);

	if (leftIndex == size)
	{
		return 0;
	}

	int rightIndex = upperBound(elem);
	return rightIndex - leftIndex + 1;
}

bool SortedCollection::contains(int elem) const
{
	return lowerBound(elem) != size;
}
