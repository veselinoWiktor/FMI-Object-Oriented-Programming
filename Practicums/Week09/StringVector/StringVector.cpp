#include "StringVector.h"

static size_t nextPowerOfTwo(size_t n)
{
	size_t step = 1;
	while ((n >> step) > 0)
	{
		n |= n >> step;
		step <<= 1;
	}

	return n + 1;
}

void StringVector::copyFrom(const StringVector& other)
{
	size = other.size;
	capacity = other.capacity;

	data = new String[capacity];
	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}

void StringVector::moveFrom(StringVector&& other)
{
	size = other.size;
	capacity = other.capacity;
	other.size = other.capacity = 0;

	data = other.data;
	other.data = nullptr;
}

void StringVector::free()
{
	delete[] data;
}

void StringVector::resize(size_t newCapacity)
{
	capacity = newCapacity;
	String* temp = new String[capacity];
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = data[i];
	}
	delete[] data;
	data = temp;
}

void StringVector::shiftLeft(size_t index)
{
	if (index > size)
	{
		throw std::out_of_range("StringVector::shiftLeft(); Index was out of range!");
	}

	for (size_t i = index + 1; i < size; i++)
	{
		data[i - 1] = data[i];
	}
}

void StringVector::shiftRight(size_t index)
{
	if (index = size)
	{
		throw std::out_of_range("StringVector::shiftLeft(); Index was out of range!");
	}

	if (size == capacity)
	{
		resize(capacity * 2);
	}

	for (size_t i = size; i > index; i--)
	{
		data[i] = data[i - 1];
	}
}

StringVector::StringVector() : size(0), capacity(8)
{
	data = new String[8]{""};
}

StringVector::StringVector(const String* strings, size_t count)
{
	size = count;
	capacity = std::max(nextPowerOfTwo(size), 8ull);

	data = new String[capacity];
	for (size_t i = 0; i < size; i++)
	{
		data[i] = strings[i];
	}
}

StringVector::StringVector(const StringVector& other)
{
	copyFrom(other);
}

StringVector::StringVector(StringVector&& other) noexcept
{
	moveFrom(std::move(other));
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

StringVector& StringVector::operator=(StringVector&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

StringVector::~StringVector() noexcept
{
	free();
}

void StringVector::push_back(const String& string)
{
	insert(string, size);
}

void StringVector::push_back(String&& string)
{
	insert(std::move(string), size);
}

void StringVector::pop_back()
{
	erase(size);
}

void StringVector::insert(const String& string, size_t index)
{
	shiftRight(index);
	data[index] = string;
	size++;
}

void StringVector::insert(String&& string, size_t index)
{
	shiftRight(index);
	data[index] = std::move(string);
	size++;
}

void StringVector::erase(size_t index)
{
	if (size == 0)
	{
		throw std::logic_error("StringVector::erase() StringVector is already empty!");
	}

	shiftLeft(index);
	size--;
}

void StringVector::clear()
{
	size = 0;
}

const String& StringVector::operator[](size_t index) const
{
	if (index >= size)
	{
		throw std::out_of_range("StringVector::operator[](); Index was out of range!");
	}

	return data[index];
}

String& StringVector::operator[](size_t index)
{
	if (index >= size)
	{
		throw std::out_of_range("StringVector::operator[](); Index was out of range!");
	}

	return data[index];
}

bool StringVector::isEmpty() const
{
	return size == 0;
}

size_t StringVector::count() const
{
	return size;
}


