#pragma once
#include "String.h"
#include <iostream>

class StringViewer
{
	const char* begin;
	const char* end; // 1 element after the final char;

public:
	StringViewer(const char* begin, const char* end);
	StringViewer(const char* str); // terminated string
	StringViewer(const String& string);

	size_t length() const;
	char operator[](size_t idx) const;

	StringViewer substr(size_t from, size_t length) const;
	friend std::ostream& operator<<(std::ostream& os, const StringViewer& strView);
};

//implement comparison operators