#include <iostream>
#include "MultiSet.h"

int main()
{
	try
	{
		MultiSet ms;
		ms.deserialize("multiset.txt");
		ms.print();
		ms.printMemory();
		MultiSet cms = ms.Complement();
		cms.print();
		cms.printMemory();
	}
	catch (const std::out_of_range& e)
	{
		std::cout << e.what();
	}
}