#pragma once
#include "ConsolePrinter.h"

class StringWrapper
{
	const char* str;
	const ConsolePrinter& cp;

public:
	StringWrapper(const char* str, const ConsolePrinter& cp);
	void print() const;
};