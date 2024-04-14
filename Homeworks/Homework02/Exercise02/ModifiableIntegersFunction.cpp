#include "ModifiableIntegersFunction.h"

ModifiableIntegersFunction::ModifiableIntegersFunction(int16_t(*functionPredicate)(int16_t))
{
	if (!functionPredicate)
	{
		return;
	}
	function = functionPredicate;

	capacity = 16;
	changedPoints = new Point[capacity];//TODO fix later;
}

void ModifiableIntegersFunction::changePoint(int16_t _x, int16_t _y)
{
	Point pt(_x, _y);
	changedPoints[count++] = pt;
}

void ModifiableIntegersFunction::disablePoint(int16_t _x, int16_t _y)
{
	Point pt(_x, _y);
	pt.isUndefined = true;
	changedPoints[count++] = pt;
}

int16_t ModifiableIntegersFunction::operator()(int16_t _x)
{
	return function(_x);
}

bool ModifiableIntegersFunction::isBijective() const
{
	if (isInjective() && isSurjective)
	{
		return true;
	}
	else
	{
		return false;
	}
}
