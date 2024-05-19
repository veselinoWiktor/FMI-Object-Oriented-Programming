#include "String.h"
#pragma warning (disable : 4996)

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

void String::resize(size_t newCapacity)
{
	_capacity = newCapacity;
	char* temp = new char[_capacity + 1];

	for (size_t i = 0; i < _size; i++)
	{
		temp[i] = _data[i];
	}

	delete[] _data;
	_data = temp;
}

void String::copyFrom(const String& other)
{
	_size = other._size;
	_capacity = other._capacity;
	_data = new char[_capacity + 1];
	for (size_t i = 0; i < _size; i++)
	{
		_data[i] = other._data[i];
	}
}

void String::free()
{
	delete[] _data;
	_size = 0;
	_capacity = 8;
}

String::String() : String("")
{
}

String::String(const char* data)
{
	if (!data)
	{
		_size = 0;
		_capacity = 8;
		_data = new char[_capacity + 1];
		strcpy(_data, "");
	}
	else
	{
		_size = strlen(data);
		_capacity = std::max(nextPowerOfTwo(_size), (size_t)8);
		_data = new char[_capacity + 1];
		strcpy(_data, data);
	}
}

String::String(const String& other)
{
	copyFrom(other);
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

String::~String()
{
	free();
}

size_t String::getCapacity() const
{
	return _capacity;
}

size_t String::getSize() const
{
	return _size;
}

const char* String::c_str() const
{
	return _data;
}

const char& String::operator[](size_t index) const
{
	return _data[index];
}

char& String::operator[](size_t index)
{
	return _data[index];
}

String& String::operator+=(const String& other)
{
	while (_capacity <= (_size + other._size))
	{
		resize(_capacity * 2);
	}

	for (size_t i = 0; i < other._size; i++)
	{
		_data[_size++] = other._data[i];
	}

	_data[_size] = '\0';

	return *this;
}

std::istream& operator>>(std::istream& is, String& obj)
{
	char buff[1024];
	is >> buff;

	size_t buffSize = strlen(buff);
	if (buffSize > obj._capacity)
	{
		obj.resize(nextPowerOfTwo(buffSize));
	}

	strcpy(obj._data, buff);
	obj._size = buffSize;
	return is;
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	if (!os.good())
	{
		return os;
	}

	os << obj._data;

	return os;

	//return os << obj._data;
}

String operator+(const String& lhs, const String& rhs)
{
	String result;
	result += lhs;
	result += rhs;
	return result;
}

bool operator==(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const String& lhs, const String& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator>=(const String& lhs, const String& rhs)
{
	return !(lhs < rhs);
}

bool operator>(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator<=(const String& lhs, const String& rhs)
{
	return !(lhs > rhs);
}
