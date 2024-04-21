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
	data = new char[capacity];
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

String::String() : data(nullptr), length(0), capacity(0)
{
}

String::String(const char* str)
{
	length = strlen(str);
	capacity = std::max(nextPowerOfTwo(length), (unsigned)16);
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
