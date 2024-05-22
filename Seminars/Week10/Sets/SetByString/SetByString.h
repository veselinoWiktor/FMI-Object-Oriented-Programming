#pragma once
#include "../Bitset/Bitset.h"

class SetByString : private BitSet
{
	char* str;

	void copyFrom(const SetByString& other);
	void moveFrom(SetByString&& other);
	void free();

	void setNumbersFromString();
public:
	SetByString(unsigned max, const char* data);
	SetByString(const SetByString& other);
	SetByString(SetByString&& other) noexcept;
	SetByString& operator=(const SetByString& other);
	SetByString& operator=(SetByString&& other) noexcept;
	~SetByString();

	void print() const;
	void setText(const char* newStr);
	void setAt(unsigned idx, char ch);
};

