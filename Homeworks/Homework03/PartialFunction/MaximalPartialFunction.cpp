#include "MaximalPartialFunction.h"

MaximalPartialFunction::MaximalPartialFunction(const Container<PartialFunction>& functions) : functions(functions)
{
}

int MaximalPartialFunction::getFunctionValue(int x) const
{
	if (!isFunctionDefinedIn(x))
	{
		return 0;
	}

	int32_t maxValue = INT32_MIN;
	size_t size = functions.getSize();
	int32_t currFunctionValue = 0;
	for (size_t i = 0; i < size; i++)
	{
		currFunctionValue = functions[i]->getFunctionValue(x);
		if (currFunctionValue > maxValue)
		{
			maxValue = currFunctionValue;
		}
	}

	return maxValue;
}

bool MaximalPartialFunction::isFunctionDefinedIn(int x) const
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

PartialFunction* MaximalPartialFunction::clone() const
{
	return new MaximalPartialFunction(*this);
}

int MaximalPartialFunction::operator()(int x) const
{
	return getFunctionValue(x);
}
