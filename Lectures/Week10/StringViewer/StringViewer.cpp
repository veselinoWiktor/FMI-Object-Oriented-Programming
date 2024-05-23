#include "StringViewer.h"

StringViewer::StringViewer(const char* begin, const char* end) : begin(begin), end(end)
{
}

StringViewer::StringViewer(const char* str) :StringViewer(str, str + strlen(str))
{
}

StringViewer::StringViewer(const String& string) : StringViewer(string.c_str())
{
}

size_t StringViewer::length() const
{
	return end - begin;
}

char StringViewer::operator[](size_t idx) const
{
	return begin[idx];
}

StringViewer StringViewer::substr(size_t from, size_t length) const
{
	if (begin + from + length > end)
	{
		throw std::out_of_range("StringViewer::substr(); substr was out of range!");
	}

	return StringViewer(begin + from, begin + from + length);
}

std::ostream& operator<<(std::ostream& os, const StringViewer& strView)
{
	const char* iter = strView.begin;
	
	while (iter != strView.end)
	{
		os << *iter;
		iter++;
	}
	return os;
}
