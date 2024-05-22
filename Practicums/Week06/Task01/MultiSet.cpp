#include "MultiSet.h"

void MultiSet::copyFrom(const MultiSet& other)
{
	maxNum = other.maxNum;
	size_t size = getArrSize(maxNum);
	set = new unsigned char[size];

	for (size_t i = 0; i < size; i++)
	{
		set[i] = other.set[i];
	}
}

void MultiSet::free()
{
	delete[] set;
	set = nullptr;
	maxNum = 0;
}

size_t MultiSet::getArrSize(int n)
{
	return ((maxNum * 2) / 8) + 1;
}

size_t MultiSet::getBucket(int n)
{
	return n / 4;
}

size_t MultiSet::getIndex(int n)
{
	return (n % 4) * 2;
}

int MultiSet::getCount(int n)
{

}

MultiSet::MultiSet(size_t maxNum)
{
	this->maxNum = maxNum;
	set = new unsigned char[getArrSize(maxNum)];
}

MultiSet::MultiSet(const MultiSet& other)
{
	copyFrom(other);
}

MultiSet::~MultiSet()
{
	free();
}

MultiSet& MultiSet::operator=(const MultiSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

void MultiSet::add(unsigned num)
{
	
}

int MultiSet::get(unsigned num)
{
	return 0;
}


