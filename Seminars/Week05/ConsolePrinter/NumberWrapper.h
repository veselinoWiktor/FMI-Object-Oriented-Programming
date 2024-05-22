#pragma once
#include "ConsolePrinter.h"

class NumberWrapper
{
private:
	int n;
	const ConsolePrinter& consolePrinter;
public:
	NumberWrapper(int n, const ConsolePrinter& cp);
	int getNumber() const;
	void print() const;
};