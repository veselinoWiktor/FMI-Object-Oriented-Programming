#include "SwapCounter.h"

unsigned SwapCounter::count = 0;

void SwapCounter::swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
	count++;
}

int SwapCounter::getCount()
{
	return count;
}

void SwapCounter::resetCount()
{
	count = 0;
}
