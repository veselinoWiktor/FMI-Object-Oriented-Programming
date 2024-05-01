#include "String.h"
#include <iostream>
#pragma warning (disable : 4996)

void String::free()
{
	delete[] data;
	length = capacity = 0;
	data = nullptr;
}

void String::copyFrom(const String& other)
{
	length = other.length;

	capacity = other.capacity;
	data = new char[capacity + 1];
	std::strcpy(data, other.data);
}

void String::moveFrom(String&& other)
{
	data = other.data;
	other.data = nullptr;

	capacity = other.capacity;
	other.capacity = 0;

	length = other.length;
	other.length = 0;
}

void String::resize()
{
	capacity *= 2;
	char* newData = new char[capacity];

	std::strcpy(newData, data);

	delete[] data;
	data = newData;
}

String::String(unsigned length)
{
	capacity = std::max(nextPowerOfTwo(length), 16u);
	data = new char[capacity + 1];
	length = 0;
	data[0] = '\0';
}

String::String() : String("")
{
}

String::String(const char* str)
{
	length = strlen(str);
	capacity = std::max(nextPowerOfTwo(length), 16u);
	data = new char[capacity + 1];
	strcpy(data, str);
}

String::String(const String& other)
{
	copyFrom(other);
}

String::String(String&& other) noexcept
{
	moveFrom(std::move(other));
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

String& String::operator=(String&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

String::~String()
{
	free();
}

unsigned String::getLength() const
{
	return length;
}

const char* String::c_str() const
{
	return data;
}

String& String::operator+=(const String& other)
{
	length += other.length;

	while (length > capacity)
	{
		resize();
	}

	strncat(data, other.data, other.length);

	return *this;
}

char& String::operator[](unsigned idx)
{
	return data[idx];
}

const char& String::operator[](unsigned idx) const
{
	return data[idx];
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.c_str();
}

std::istream& operator>>(std::istream& is, String& obj)
{
	char buff[1024];
	is >> buff;
	unsigned buffStrLen = strlen(buff);

	while (buffStrLen > obj.capacity)
		obj.resize();

	strcpy(obj.data, buff);
	obj.length = buffStrLen;

	return is;
}

String operator+(const String& lhs, const String& rhs)
{
	String result(lhs.length + rhs.length);

	result += lhs;
	result += rhs;

	return result;
}

bool operator==(const String& lhs, const String& rhs)
{
	return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const String& lhs, const String& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const String& lhs, const String& rhs)
{
	return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const String& lhs, const String& rhs)
{
	return !(lhs > rhs);
}

bool operator>(const String& lhs, const String& rhs)
{
	return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator>=(const String& lhs, const String& rhs)
{
	return !(lhs < rhs);
}

unsigned nextPowerOfTwo(unsigned num)
{
	unsigned step = 1;

	while ((num >> step) > 0)
	{
		num |= (num >> step);
		step <<= 1;
	}

	return num + 1;
}
