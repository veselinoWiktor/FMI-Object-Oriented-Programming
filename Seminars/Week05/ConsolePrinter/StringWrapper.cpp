#include "StringWrapper.h"

StringWrapper::StringWrapper(const char* str, const ConsolePrinter& cp) : str(str), cp(cp)
{
}

void StringWrapper::print() const
{
	cp.print(str);
}


