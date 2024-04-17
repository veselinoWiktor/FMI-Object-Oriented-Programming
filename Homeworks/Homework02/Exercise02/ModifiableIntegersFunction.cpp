#include "ModifiableIntegersFunction.h"

void ModifiableIntegersFunction::copyFrom(const ModifiableIntegersFunction& other)
{
	disabledCapacity = other.disabledCapacity;
	disabledCount = other.disabledCount;
	
	disabledPoints = new int16_t[disabledCapacity];
	
	for (size_t i = 0; i < disabledCount; i++)
	{
		disabledPoints[i] = other.disabledPoints[i]; //might have some problem
	}

	for (size_t i = 0; i < Constants::FUNCTION_VALUES_COUNT; i++)
	{
		functionValues[i] = other.functionValues[i];
	}
}

void ModifiableIntegersFunction::free()
{
	delete[] disabledPoints;
	function = nullptr;
	disabledPoints = nullptr;
	disabledCapacity = disabledCount = 0;
}

void ModifiableIntegersFunction::resize()
{
	disabledCapacity *= 2;
	int16_t* newDisabledPoints = new int16_t[disabledCapacity];

	for (size_t i = 0; i < disabledCount; i++)
	{
		newDisabledPoints[i] = disabledPoints[i];
	}

	delete[] disabledPoints;
	disabledPoints = newDisabledPoints;
}

void ModifiableIntegersFunction::initFunctionData()
{
	for (size_t i = 0; i < Constants::FUNCTION_VALUES_COUNT; i++)
	{
		functionValues[i] = function(i - Constants::FUNCTION_ZERO_INDEX);
	}

	disabledCapacity = 16;
	disabledCount = 0;
	disabledPoints = new int16_t[disabledCapacity];
}

void ModifiableIntegersFunction::setFunction(int16_t(*functionPredicate)(int16_t))
{
	if (!functionPredicate)
	{
		throw std::invalid_argument("Nullptr was given.");
	}

	function = functionPredicate;
}

bool ModifiableIntegersFunction::isDisabled(int16_t _x) const
{
	for (size_t i = 0; i < disabledCount; i++)
	{
		if (disabledPoints[i] == _x)
		{
			return true;
		}
	}

	return false;
}

ModifiableIntegersFunction::ModifiableIntegersFunction(int16_t(*functionPredicate)(int16_t))
{
	setFunction(functionPredicate);
	initFunctionData();
}

ModifiableIntegersFunction::ModifiableIntegersFunction(const ModifiableIntegersFunction& other)
{
	copyFrom(other);
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator=(const ModifiableIntegersFunction& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

ModifiableIntegersFunction::~ModifiableIntegersFunction()
{
	free();
}

void ModifiableIntegersFunction::changePoint(int16_t _x, int16_t _y)
{
	functionValues[_x + Constants::FUNCTION_ZERO_INDEX] = _y;
}

void ModifiableIntegersFunction::disablePoint(int16_t _x)
{
	if (disabledCount == disabledCapacity)
	{
		resize();
	}

	disabledPoints[disabledCount++] = _x;
}

int16_t ModifiableIntegersFunction::operator()(int16_t _x)
{
	if (isDisabled(_x))
	{
		throw std::invalid_argument("Point is disabled.");
	}

	return functionValues[_x + Constants::FUNCTION_ZERO_INDEX];
}
