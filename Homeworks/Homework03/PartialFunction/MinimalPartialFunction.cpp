#include "MinimalPartialFunction.h"

MinimalPartialFunction::MinimalPartialFunction(const Container<PartialFunction>& functions) : functions(functions)
{
}

int MinimalPartialFunction::getFunctionValue(int x) const
{
	if (!isFunctionDefinedIn(x))
	{
		return 0;
	}

	int32_t minValue = INT32_MAX;
	size_t size = functions.getSize();
	int32_t currFunctionValue = 0;
	for (size_t i = 0; i < size; i++)
	{
		currFunctionValue = functions[i]->getFunctionValue(x);
		if (currFunctionValue < minValue)
		{
			minValue = currFunctionValue;
		}
	}

	return minValue;
}

bool MinimalPartialFunction::isFunctionDefinedIn(int x) const
{
	size_t size = functions.getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (!functions[i]->isFunctionDefinedIn(x))
		{
			return false;
		}
	}
	return true;
}

PartialFunction* MinimalPartialFunction::clone() const
{
	return new MinimalPartialFunction(*this);
}

int MinimalPartialFunction::operator()(int x) const
{
	return getFunctionValue(x);
}
