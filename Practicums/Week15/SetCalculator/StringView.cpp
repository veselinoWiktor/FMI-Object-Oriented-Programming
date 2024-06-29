#include "StringView.h"

StringView::StringView(const char* begin, const char* end)
	: begin(begin), end(end)
{
}

StringView::StringView(const char* str)
	: StringView(str, str + strlen(str))
{
}

size_t StringView::length() const
{
	return end - begin;
}

char StringView::operator[](size_t idx)
{
	if (begin + idx >= end)
	{
		throw std::out_of_range("Index was out of range!");
	}

	return begin[idx];
}

StringView StringView::substr(size_t from, size_t length)
{
	if (begin + from + length > end)
	{
		throw std::length_error("Substr was out of range!");
	}

	return StringView(begin + from, begin + from + length);
}
