#include "SetByString.h"
#include <sstream>

void SetByString::copyFrom(const SetByString& other)
{
	str = new char[strlen(other.str) + 1];
	strcpy(str, other.str);
}

void SetByString::moveFrom(SetByString&& other)
{
	str = other.str;
	other.str = nullptr;
}

void SetByString::free()
{
	delete[] str;
}

void SetByString::setNumbersFromString()
{
	std::stringstream ss(str);
	while (!ss.eof())
	{
		unsigned curr;
		ss >> curr;
		BitSet::add(curr);
	}

}

SetByString::SetByString(unsigned max, const char* data) : BitSet(max)
{
	str = new char[strlen(data) + 1];
	strcpy(str, data);
	setNumbersFromString();
}

SetByString::SetByString(const SetByString& other) : BitSet(other)
{
	copyFrom(other);
}

SetByString::SetByString(SetByString&& other) noexcept : BitSet(std::move(other))
{
	moveFrom(std::move(other));
}

SetByString& SetByString::operator=(const SetByString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

SetByString& SetByString::operator=(SetByString&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

SetByString::~SetByString()
{
	free();
}

void SetByString::print() const
{
	BitSet::print();
}

void SetByString::setText(const char* newStr)
{
	if (!newStr)
	{
		throw std::exception("Nullptr");
	}

	delete[] str;
	str = new char[strlen(newStr) + 1];
	strcpy(str, newStr);
	BitSet::clear();
	setNumbersFromString();
}

void SetByString::setAt(unsigned idx, char ch)
{
	str[idx] = ch;
	BitSet::clear();
	setNumbersFromString();
}
