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

int16_t ModifiableIntegersFunction::operator()(int16_t _x) const
{
	if (isDisabled(_x))
	{
		throw std::invalid_argument("Point is disabled.");
	}

	return functionValues[_x + Constants::FUNCTION_ZERO_INDEX];
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator+=(const ModifiableIntegersFunction& other)
{
	while ((disabledCount + other.disabledCount) > disabledCapacity)
	{
		resize();
	}

	for (size_t i = 0; i < other.disabledCount; i++)
	{
		if (isDisabled(other.disabledPoints[i]))
		{
			continue;
		}

		disabledPoints[disabledCount++] = other.disabledPoints[i];
	}

	for (size_t i = 0; i < Constants::FUNCTION_VALUES_COUNT; i++)
	{
		functionValues[i] += other.functionValues[i];
	}
	
	return *this;
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator-=(const ModifiableIntegersFunction& other)
{
	while ((disabledCount + other.disabledCount) > disabledCapacity)
	{
		resize();
	}

	for (size_t i = 0; i < other.disabledCount; i++)
	{
		if (isDisabled(other.disabledPoints[i]))
		{
			continue;
		}

		disabledPoints[disabledCount++] = other.disabledPoints[i];
	}

	for (size_t i = 0; i < Constants::FUNCTION_VALUES_COUNT; i++)
	{
		functionValues[i] -= other.functionValues[i];
	}

	return *this;
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator^(int16_t power)
{
	if (power < 0)
	{
		if (power % 2 == 0) // (f^-1)^-1 = f тоест за всяка четна отрицателна степен функцията се запазва
		{
			return *this;
		}
		else
		{
			//reverse function
		}
	}
	else if (power == 0)
	{
		for (size_t i = 0; i < Constants::FUNCTION_VALUES_COUNT; i++)
		{
			functionValues[i] = 1;
		}
	}
	else if (power == 1)
	{
		return *this;
	}
	else {
		for (size_t i = 0; i < Constants::FUNCTION_VALUES_COUNT; i++)
		{
			functionValues[i] = powerOf(functionValues[i], power);
		}
	}
}

ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	ModifiableIntegersFunction mfsResult = lhs;
	mfsResult += rhs;

	return mfsResult;
}

ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	ModifiableIntegersFunction mfsResult = lhs;
	mfsResult -= rhs;

	return mfsResult;
}

bool operator||(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	int16_t difference = lhs(Constants::FUNCTION_LOWER_BOUND_INDEX) - rhs(Constants::FUNCTION_LOWER_BOUND_INDEX);

	for (int16_t i = Constants::FUNCTION_LOWER_BOUND_INDEX + 1; i <= Constants::FUNCTION_UPPER_BOUND_INDEX; i++)
	{
		if ((lhs(i) - rhs(i)) != difference)
		{
			return false;
		}
	}

	return true;
}

bool operator==(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int16_t i = Constants::FUNCTION_LOWER_BOUND_INDEX; i <= Constants::FUNCTION_UPPER_BOUND_INDEX; i++)
	{
		if (lhs(i) != rhs(i))
		{
			return false;
		}
	}
	
	return true;
}

bool operator!=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int16_t i = Constants::FUNCTION_LOWER_BOUND_INDEX; i <= Constants::FUNCTION_UPPER_BOUND_INDEX; i++)
	{
		if (lhs(i) >= rhs(i))
		{
			return false;
		}
	}

	return true;
}

bool operator<=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	return !(lhs > rhs);
}

bool operator>(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int16_t i = Constants::FUNCTION_LOWER_BOUND_INDEX; i <= Constants::FUNCTION_UPPER_BOUND_INDEX; i++)
	{
		if (lhs(i) <= rhs(i))
		{
			return false;
		}
	}

	return true;
}

bool operator>=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	return !(lhs < rhs);
}

int16_t powerOf(int16_t base, uint16_t power)
{
	if (power == 0)
	{
		return 1;
	}
	else if (base == 0 || base == 1)
	{
		return base;
	}

	int result = 1;
	for (size_t i = 0; i < power; i++)
	{
		result *= base;
	}

	return result;
}

