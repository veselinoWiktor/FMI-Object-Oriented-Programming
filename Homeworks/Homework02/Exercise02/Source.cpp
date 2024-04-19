#include <iostream>
#include "ModifiableIntegersFunction.h"

int16_t f(int16_t x)
{
	return x * x;
}

int16_t g(int16_t x)
{
	return x + 5;
}

int16_t h(int16_t x)
{
	return x;
}

int16_t l(int16_t x)
{
	return 3;
}

int main()
{
	ModifiableIntegersFunction mih(f);
	mih.draw(-10, -1);

	std::cout << mih.isInjective() << std::endl;

	ModifiableIntegersFunction mif(f);
	ModifiableIntegersFunction mig(g);

	ModifiableIntegersFunction miz(mif);

	ModifiableIntegersFunction compos = mif * mig;

	std::cout << mig.isInjective() << std::endl;
	std::cout << compos(0) <<std::endl;
	std::cout << compos(1) << std::endl;
	std::cout << compos(2) << std::endl;
	std::cout << compos(3) << std::endl;

	std::cout << mif(0) << std::endl;
	std::cout << mif(1) << std::endl;
	std::cout << mif(2) << std::endl;
	std::cout << mif(3) << std::endl;
	std::cout << mif(4) << std::endl;
	std::cout << mif(5) << std::endl;
	std::cout << mif(90) << std::endl;
	std::cout << powerOf(2, 3) << std::endl;

}