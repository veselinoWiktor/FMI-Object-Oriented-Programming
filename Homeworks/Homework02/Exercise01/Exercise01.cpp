#include <iostream>
#include "MultiSet.h"

int main()
{
	MultiSet ms(20, 3);
	std::cout << ms.containsCount(5) << std::endl;
}