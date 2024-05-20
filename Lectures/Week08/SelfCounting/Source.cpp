#include "SelfCounting.h"
#include <iostream>

int main()
{
	SelfCounting s1(3);
	SelfCounting s2(31);

	{
		SelfCounting s3(232);

		std::cout << SelfCounting::getCreatedCount() << " " << SelfCounting::getLiveObjectsCount() << std::endl;
	}

	std::cout << SelfCounting::getCreatedCount() << " " << SelfCounting::getLiveObjectsCount() << std::endl;
}