#include "ModifiableIntegersFunction.h"
#include "MultiSet.h"
#include <fstream>

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

void ModifiableIntegersFunction::initFunctionData(int16_t(*functionPredicate)(int16_t))
{
	for (size_t i = 0; i < Constants::FUNCTION_VALUES_COUNT; i++)
	{
		functionValues[i] = functionPredicate(i - Constants::FUNCTION_ZERO_INDEX);
	}

	disabledCapacity = 16;
	disabledCount = 0;
	disabledPoints = new int16_t[disabledCapacity];
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

ModifiableIntegersFunction::ModifiableIntegersFunction()
{
	int16_t(*defaultFunction)(int16_t) = [](int16_t x) { return (int16_t)0; };
	initFunctionData(defaultFunction);
}

ModifiableIntegersFunction::ModifiableIntegersFunction(int16_t(*functionPredicate)(int16_t))
{
	initFunctionData(functionPredicate);
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

ModifiableIntegersFunction ModifiableIntegersFunction::operator^(int16_t power)
{
	if (power < 0)
	{
		if (power % 2 == 0) // (f^-1)^-1 = f тоест за всяка четна отрицателна степен функцията се запазва
		{
			return *this;
		}
		else // за всяка нечетна отрицателна степен функцията се обръща
		{
			if (!isInjective())
			{
				throw std::logic_error("The function is irreversible");
			}


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
	else 
	{
		for (size_t i = 0; i < Constants::FUNCTION_VALUES_COUNT; i++)
		{
			functionValues[i] = powerOf(functionValues[i], power);
		}
	}
}

bool ModifiableIntegersFunction::isInjective() const
{
	MultiSet ms(Constants::FUNCTION_VALUES_COUNT - 1, 1);

	int16_t currValue;
	for (size_t i = 0; i < Constants::FUNCTION_VALUES_COUNT; i++)
	{
		currValue = functionValues[i];

		if (ms.containsCount(currValue + Constants::FUNCTION_ZERO_INDEX) == 1)
		{
			return false;
		}
		
		ms.addNumber(currValue + Constants::FUNCTION_ZERO_INDEX);
	}

	return true;
}

bool ModifiableIntegersFunction::isSurjective() const
{
	if (disabledCount > 0)
	{
		return false;
	}
	
	return true;
}

bool ModifiableIntegersFunction::isBijective() const
{
	if (isInjective() && isSurjective())
	{
		return true;
	}

	return false;
}

void ModifiableIntegersFunction::serialize(const char* filename) const
{
	if (!filename)
	{
		throw std::invalid_argument("filename was nullptr");
	}

	std::ofstream ofs(filename, std::ios::binary);
	if (!ofs.is_open())
	{
		throw std::runtime_error("stream is already opened");
	}

	ofs.write((const char*)&disabledCount, sizeof(int16_t));
	ofs.write((const char*)disabledPoints, sizeof(int16_t) * disabledCount);
	ofs.write((const char*)functionValues, sizeof(int16_t) * Constants::FUNCTION_VALUES_COUNT);

	ofs.close();
}

void ModifiableIntegersFunction::desrialize(const char* filename)
{
	if (!filename)
	{
		throw std::invalid_argument("filename was nullptr");
	}

	std::ifstream ifs(filename, std::ios::binary);
	if (!ifs.is_open())
	{
		throw std::runtime_error("stream is already opened");
	}

	ifs.read((char*)&disabledCount, sizeof(int16_t));
	disabledCapacity = std::max(nextPowerOfTwo(disabledCount), (unsigned)16);
	
	delete[] disabledPoints;
	disabledPoints = new int16_t[disabledCapacity];

	ifs.read((char*)disabledPoints, sizeof(int16_t) * disabledCount);
	ifs.read((char*)functionValues, sizeof(int16_t) * Constants::FUNCTION_VALUES_COUNT);
	ifs.close();
}

void ModifiableIntegersFunction::draw(int16_t startX, int16_t startY) const
{
	int16_t endX = startX + 19;
	int16_t endY = startY + 19;

	for (int i = endY; i >= startY; i--)
	{
		for (int j = startX; j <= endX; j++)
		{
			if (isDisabled(j))
			{
				std::cout << "  ";
				continue;
			}

			if (functionValues[j + Constants::FUNCTION_ZERO_INDEX] == i)
			{
				std::cout << "()";
			}
			else
			{
				std::cout << "  ";
			}
		}

		std::cout << std::endl;
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

//Composition operator
ModifiableIntegersFunction operator*(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	ModifiableIntegersFunction mfsCompositionResult;

	int16_t newValue = 0;
	bool isLhsValueDisabled = false;
	bool isRhsValueDisabled = false;
	for (int16_t i = Constants::FUNCTION_LOWER_BOUND_INDEX; i <= Constants::FUNCTION_UPPER_BOUND_INDEX; i++)
	{
		isLhsValueDisabled = lhs.isDisabled(i);
		isRhsValueDisabled = rhs.isDisabled(i);

		if (isLhsValueDisabled || isRhsValueDisabled)
		{
			mfsCompositionResult.disablePoint(i);
			continue;
		}

		newValue = lhs(rhs(i));
		mfsCompositionResult.changePoint(i, newValue);

		if (i == Constants::FUNCTION_UPPER_BOUND_INDEX)
		{
			break;
		}
	}

	return mfsCompositionResult;
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
	bool isLhsValueDisabled = false;
	bool isRhsValueDisabled = false;
	for (int16_t i = Constants::FUNCTION_LOWER_BOUND_INDEX; i <= Constants::FUNCTION_UPPER_BOUND_INDEX; i++)
	{
		isLhsValueDisabled = lhs.isDisabled(i);
		isRhsValueDisabled = rhs.isDisabled(i);

		if ((isLhsValueDisabled && !isRhsValueDisabled)
			|| (!isLhsValueDisabled && isRhsValueDisabled))
		{
			return false;
		}
		else if (isLhsValueDisabled && isRhsValueDisabled)
		{
			continue;
		}

		if (lhs(i) != rhs(i))
		{
			return false;
		}

		if (i == Constants::FUNCTION_UPPER_BOUND_INDEX)
		{
			break;
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
	bool isLhsValueDisabled = false;
	bool isRhsValueDisabled = false;
	for (int16_t i = Constants::FUNCTION_LOWER_BOUND_INDEX; i <= Constants::FUNCTION_UPPER_BOUND_INDEX; i++)
	{
		isLhsValueDisabled = lhs.isDisabled(i);
		isRhsValueDisabled = rhs.isDisabled(i);

		if (isLhsValueDisabled && isRhsValueDisabled)
		{
			return false;
		}
		else if (!isLhsValueDisabled && isRhsValueDisabled)
		{
			return false;
		}

		if (lhs(i) >= rhs(i))
		{
			return false;
		}

		if (i == Constants::FUNCTION_UPPER_BOUND_INDEX)
		{
			break;
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
	bool isLhsValueDisabled = false;
	bool isRhsValueDisabled = false;
	for (int16_t i = Constants::FUNCTION_LOWER_BOUND_INDEX; i <= Constants::FUNCTION_UPPER_BOUND_INDEX; i++)
	{
		isLhsValueDisabled = lhs.isDisabled(i);
		isRhsValueDisabled = rhs.isDisabled(i);

		if (isLhsValueDisabled && isRhsValueDisabled)
		{
			return false;
		}
		else if (isLhsValueDisabled && !isRhsValueDisabled)
		{
			return false;
		}

		if (lhs(i) <= rhs(i))
		{
			return false;
		}

		if (i == Constants::FUNCTION_UPPER_BOUND_INDEX)
		{
			break;
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

uint32_t nextPowerOfTwo(uint16_t n)
{
	uint16_t step = 1;

	while ((n >> step) > 0) {
		n |= n >> step;
		step <<= 1;
	}

	return n + 1;
}

