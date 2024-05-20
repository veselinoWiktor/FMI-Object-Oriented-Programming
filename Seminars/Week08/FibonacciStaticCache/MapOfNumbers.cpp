#include "MapOfNumbers.h"
#include <iostream>

MapOfNumbers::MapOfNumbers(unsigned nullValue)
{
	for (size_t i = 0; i < N; i++)
	{
		_values[i] = nullValue;
	}
	_nullValue = nullValue;
}

void MapOfNumbers::add(unsigned key, unsigned value)
{
	if (value == _nullValue)
	{
		return;
	}

	_values[key] = value;
}

bool MapOfNumbers::contains(unsigned key) const
{
	return _values[key] != _nullValue;
}

unsigned MapOfNumbers::getValue(unsigned key) const
{
	if (!contains(key))
	{
		throw std::invalid_argument("Error");
	}
	return _values[key];
}

