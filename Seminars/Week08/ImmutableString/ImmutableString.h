#pragma once
#include "StringPool.h"
#include <iostream>

class ImmutableString
{
private:
	const char* data;
	size_t length;

	static StringPool pool;

	void copyFrom(const ImmutableString& other);
	void free();

public:
	ImmutableString();
	ImmutableString(const char* str);
	ImmutableString(const ImmutableString& other);
	ImmutableString& operator=(const ImmutableString& other);
	~ImmutableString();

	const char* c_str() const;
	size_t getLength() const;
	bool isEmpty() const;

	char operator[](size_t index) const;
};
std::ostream& operator<<(std::ostream os, const ImmutableString& str);

bool operator==(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator!=(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator<(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator>=(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator>(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator<=(const ImmutableString& lhs, const ImmutableString& rhs);



