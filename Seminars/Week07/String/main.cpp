#include "String.h"

int main()
{
	String str("Viktorr");
	str += "r";
	std::cout << str << std::endl;
	std::cout << str.getSize() << std::endl;
	std::cout << str.getCapacity() << std::endl;
}