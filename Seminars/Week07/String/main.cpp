#include "String.h"

size_t nextPowerOfTwoo(size_t n)
{
	size_t step = 1;

	while ((n >> step) > 0)
	{
		n |= n >> step;
		step <<= 1;
	}

	return n + 1;
}

int main()
{
	String str1("Viktorr");
	String str2(" e gotin!");
	String str = str1 + str2;
	std::cin >> str;
	std::cout << str << std::endl;
	std::cout << str.getSize() << std::endl;
	std::cout << str.getCapacity() << std::endl;
}
