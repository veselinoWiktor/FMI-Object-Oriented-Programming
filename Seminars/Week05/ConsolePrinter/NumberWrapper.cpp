#include "NumberWrapper.h"
#include <string>

NumberWrapper::NumberWrapper(int n, const ConsolePrinter& cp)
	:n(n), consolePrinter(cp)
{

}

int NumberWrapper::getNumber() const
{
	return n;
}

void NumberWrapper::print() const
{
	consolePrinter.print(std::to_string(n).c_str());
}


