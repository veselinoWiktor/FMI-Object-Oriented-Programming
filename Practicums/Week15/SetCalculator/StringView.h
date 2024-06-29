#pragma once
#include <iostream>

class StringView
{
private:
	const char* begin;
	const char* end;

public:
	StringView(const char* begin, const char* end);
	StringView(const char* str);

	size_t length() const;
	char operator[](size_t idx);

	StringView substr(size_t from, size_t length);
};

