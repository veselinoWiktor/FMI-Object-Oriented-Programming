#include <iostream>
#include "ModifiableIntegersFunction.h"

int16_t f(int16_t x)
{
	return;
}

int main()
{
	ModifiableIntegersFunction mif(f);

	std::cout << mif(0) << std::endl;
	std::cout << mif(1) << std::endl;
	std::cout << mif(2) << std::endl;
	std::cout << mif(3) << std::endl;
	std::cout << mif(4) << std::endl;
	std::cout << mif(5) << std::endl;
	std::cout << mif(90) << std::endl;


}