#include "ModifiableIntegersFunction.h"

int16_t f(int16_t x)
{
	return x * 2;
}

int main()
{
	ModifiableIntegersFunction mif(f);

	std::cout << mif(1000);
}