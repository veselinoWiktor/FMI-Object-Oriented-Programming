#include <iostream>
#include <fstream>
#include "SetCalculator.h"


int main()
{
	SetCalculator sc("func.txt");
	std::cout << sc.accepts(1) << std::endl;
	std::cout << sc.accepts(2) << std::endl;
	std::cout << sc.accepts(3) << std::endl;
}