#include <iostream>
#include "ConsolePrinter.h"
#include "StringWrapper.h"
#include "NumberWrapper.h"

int main()
{
	{
		ConsolePrinter noNumbers([](char ch) {return ch >= '0' && ch <= '9'; });

		StringWrapper sr("Test3432wrwe", noNumbers);
		NumberWrapper nw(12345, noNumbers);

		sr.print();
		nw.print();
	}
	{
		ConsolePrinter censoreEverything([](char ch) {return true; });

		StringWrapper sr("Test3432wrwe", censoreEverything);
		NumberWrapper nw(12345, censoreEverything);

		sr.print();
		nw.print();
	}
}