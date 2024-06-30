#include "SetCalculator.h"

bool SetCalculator::accepts(unsigned int x)
{
	return set->accepts(x);
}

void SetCalculator::copyFrom(const SetCalculator& other)
{
	set = other.set->clone();
}

void SetCalculator::moveFrom(SetCalculator&& other)
{
	set = other.set;
	other.set = nullptr;
}

void SetCalculator::free()
{
	delete set;
}

SetCalculator::SetCalculator(const char* filePath)
{
	if (!filePath)
	{
		throw std::invalid_argument("invalid filePath");
	}
	set = SetFactory::createSet(filePath);
}

SetCalculator::SetCalculator(const SetCalculator& other)
{
	copyFrom(other);
}

SetCalculator& SetCalculator::operator=(const SetCalculator& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

SetCalculator::SetCalculator(SetCalculator&& other) noexcept
{
	moveFrom(std::move(other));
}

SetCalculator& SetCalculator::operator=(SetCalculator&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

SetCalculator::~SetCalculator()
{
	free();
}
