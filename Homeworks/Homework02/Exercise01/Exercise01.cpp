#include <iostream>
#include "MultiSet.h"

int main()
{
	MultiSet ms(15, 3);
	ms.addNumber(0);
	ms.addNumber(1);
	ms.addNumber(2);
	ms.addNumber(3);
	ms.addNumber(4);
	ms.addNumber(15);
	MultiSet cms = ms.Complement();
	std::cout << ms.containsCount(5) << std::endl;
	ms.print();
	ms.printMemory();
	cms.printMemory();
}