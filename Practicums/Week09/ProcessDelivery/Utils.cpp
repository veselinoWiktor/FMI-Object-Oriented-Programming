#include "Utils.h"

size_t Utils::nextPowerOfTwo(size_t n)
{
	size_t step = 1;
	while ((n >> step) > 0)
	{
		n |= n >> step;
		step <<= 1;
	}

	return n + 1;
}
