#include "ImmutableString.h"

StringPool ImmutableString::pool;

void ImmutableString::copyFrom(const ImmutableString& other)
{
	length = other.length;
	data = pool.getString(other.data);
}

void ImmutableString::free()
{
	pool.releaseString(data);
	data = nullptr;
}

ImmutableString::ImmutableString() : ImmutableString("")
{
}

ImmutableString::ImmutableString(const char* str)
{
	data = pool.getString(str);
	length = strlen(data);
}

ImmutableString::ImmutableString(const ImmutableString& other)
{
	copyFrom(other);
}

ImmutableString& ImmutableString::operator=(const ImmutableString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

ImmutableString::~ImmutableString()
{
	free();
}

const char* ImmutableString::c_str() const
{
	return data;
}

size_t ImmutableString::getLength() const
{
	return length;
}

bool ImmutableString::isEmpty() const
{
	return length == 0;
}

char ImmutableString::operator[](size_t index) const
{
	if (index >= length)
	{
		throw std::out_of_range("String::operator[] out of range!");
	}

	return data[index];
}

std::ostream& operator<<(std::ostream& os, const ImmutableString& str)
{
	return os << str.c_str();
}

bool operator==(const ImmutableString& lhs, const ImmutableString& rhs)
{
	return lhs.c_str() == rhs.c_str();
}

bool operator!=(const ImmutableString& lhs, const ImmutableString& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const ImmutableString& lhs, const ImmutableString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator>=(const ImmutableString& lhs, const ImmutableString& rhs)
{
	return !(lhs < rhs);
}

bool operator>(const ImmutableString& lhs, const ImmutableString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator<=(const ImmutableString& lhs, const ImmutableString& rhs)
{
	return !(lhs > rhs);
}