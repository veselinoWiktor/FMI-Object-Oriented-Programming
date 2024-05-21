#include <iostream>
#include "DynamicArrayOfA.h"

int main()
{
	DynamicArray arr(3);
	arr.pushBack(A());
	arr.pushBack(A());
	arr.pushBack(A());

	DynamicArray arr2 = std::move(arr);
	A a{ 1,3 };
	A a2{ 3,3 };
	arr2.setAtIndex(std::move(a), 2);

	size_t arrSize = arr2.getSize();
	for (size_t i = 0; i < arrSize; i++)
	{
		std::cout << arr2[i].a << " ";
	}


	arr2.setAtIndex(std::move(a2), 2);

	arr2.popBack();
	arr2[1].a = 7;
	arrSize = arr2.getSize();
	for (size_t i = 0; i < arrSize; i++)
	{
		std::cout << arr2[i].a << " ";
	}
	
	std::cout << std::endl << arr2[1].a;
	
}