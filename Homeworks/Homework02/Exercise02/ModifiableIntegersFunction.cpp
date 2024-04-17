#include "ModifiableIntegersFunction.h"

void ModifiableIntegersFunction::setFunction(int16_t(*functionPredicate)(int16_t))
{
	if (!function)
	{
		throw std::invalid_argument("Nullptr was given.");
	}

	function = functionPredicate;
}

ModifiableIntegersFunction::ModifiableIntegersFunction(int16_t(*functionPredicate)(int16_t))
{
	setFunction(functionPredicate);

}

void ModifiableIntegersFunction::changePoint(int16_t _x, int16_t _y)
{
	
}

void ModifiableIntegersFunction::disablePoint(int16_t _x, int16_t _y)
{
	
}



int16_t ModifiableIntegersFunction::operator()(int16_t _x)
{
	return function(_x);
}

//bool ModifiableIntegersFunction::isBijective() const
//{
//	if (isInjective() && isSurjective())
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
