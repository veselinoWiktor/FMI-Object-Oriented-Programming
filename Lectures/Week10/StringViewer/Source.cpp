#include "String.h"
#include <iostream>

int main()
{
	String s("viktor");
	String v = s.substr(2, 3);
	std::cout << v;
}