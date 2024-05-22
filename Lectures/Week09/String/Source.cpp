#include<iostream>
#include "String.h"

int main()
{
	String str = "012345678912345";
	str += str;
	std::cin >> str;
	std::cout << str.getLength() << std::endl;
	std::cout << str << std::endl;
}