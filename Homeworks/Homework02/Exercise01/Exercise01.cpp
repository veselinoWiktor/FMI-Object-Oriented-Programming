#include <iostream>
#include "MultiSet.h"

int main()
{
	/*try
	{
		MultiSet ms;
		ms.deserialize("multiset.txt");
		ms.print();
		ms.printMemory();
		MultiSet cms = ms.Complement();
		cms.print();
		cms.printMemory();

		MultiSet intersection = Intersect(ms, cms);
		intersection.print();
		intersection.printMemory();

		MultiSet difference = Differnce(cms, intersection);
		difference.print();
		difference.printMemory();
	}
	catch (const std::out_of_range& e)
	{
		std::cout << e.what();
	}*/

	MultiSet ms(10, 1);
	ms.addNumber(0);
	ms.addNumber(1);
	ms.addNumber(2);
	ms.addNumber(3);
	ms.addNumber(10);

	ms.printMemory();

	/*MultiSet ms2(3, 3);



	intersection.printMemory();*/

}