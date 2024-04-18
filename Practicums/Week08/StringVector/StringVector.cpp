#include "StringVector.h"
#include <cmath>

void StringVector::free()
{
	delete[] data;
	data = nullptr;
	size = capacity = 0;
}

void StringVector::copyFrom(const StringVector& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new String[capacity];

	for (int i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}

void StringVector::resize()
{
	capacity *= 2;
	String* newData = new String[capacity];

	for (int i = 0; i < size; i++)
	{
		newData[i] = data[i];
	}
	
	delete[] data;
	data = newData;
}

void StringVector::setSize(unsigned _size)
{
	size = _size;
}

void StringVector::setCapacity()
{
	capacity = std::max(getNextPowerOfTwo(size), (unsigned)16);
}

void StringVector::initData(const String* strings)
{
	data = new String[capacity];
	for (unsigned i = 0; i < size; i++)
	{
		data[i] = strings[i];
	}
}

void StringVector::shiftLeftByOne(unsigned atIdx)
{
	for (int i = atIdx; i < size - 1; i++)
	{
		data[i] = data[i + 1];
	}
}

void StringVector::shiftRightByOne(unsigned atIdx)
{
	if (size == capacity)
	{
		resize();
	}

	for (int i = atIdx; i < size; i++)
	{
		data[i + 1] = data[i];
	}
}

StringVector::StringVector(const String* strings, unsigned _size)
{
	setSize(_size);
	setCapacity();
	initData(strings);
}

StringVector::StringVector(const StringVector& other)
{
	copyFrom(other);
}

StringVector& StringVector::operator=(const StringVector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

StringVector::~StringVector()
{
	free();
}

unsigned StringVector::getSize() const
{
	return size;
}

bool StringVector::isEmpty() const
{
	return size == 0;
}

unsigned StringVector::push_back(const String& str)
{
	insert(str, size);
	return size - 1;
}

void StringVector::pop_back()
{
	if (size < 1)
	{
		throw std::logic_error("There are no elements in the StringVector");
	}

	erase(size - 1);
}

void StringVector::erase(unsigned idx)
{
	if (idx >= size)
	{
		throw std::out_of_range("Index was out of range");
	}

	shiftLeftByOne(idx);

	size--;
}

void StringVector::insert(const String& str, unsigned idx)
{
	if (idx > size)
	{
		throw std::out_of_range("Index was out of range");
	}

	shiftRightByOne(idx);

	data[idx] = str;
	size++;
}

void StringVector::clear()
{
	free();

	capacity = 16;
	data = new String[capacity];
}

String& StringVector::operator[](unsigned idx)
{
	return data[idx];
}

const String& StringVector::operator[](unsigned idx) const
{
	return data[idx];
}