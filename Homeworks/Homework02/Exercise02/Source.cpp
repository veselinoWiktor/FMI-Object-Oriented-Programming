#include <iostream>
#include "ModifiableIntegersFunction.h"

int16_t f(int16_t x)
{
	return 1;
}

int16_t g(int16_t x)
{
	return 2*x;
}

int main()
{
	ModifiableIntegersFunction mif(f);
	ModifiableIntegersFunction mig(g);
	std::cout << (mif || mig);


	/*std::cout << mif(0) << std::endl;
	std::cout << mif(1) << std::endl;
	std::cout << mif(2) << std::endl;
	std::cout << mif(3) << std::endl;
	std::cout << mif(4) << std::endl;
	std::cout << mif(5) << std::endl;
	std::cout << mif(90) << std::endl;
	std::cout << powerOf(2, 3) << std::endl;*/

}