#include<iostream>
#include "String.h"

int main()
{
	String str = "012345678912345";
	str += "viktor";
	std::cout << str.getLength() << std::endl;
	std::cout << str << std::endl;
	std::cin >> str >> std::endl;
}