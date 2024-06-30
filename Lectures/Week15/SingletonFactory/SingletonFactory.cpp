#include "SingletonFactory.h"

SingletonFactory::SingletonFactory()
{
	std::ifstream ifs("data.txt");
	if (!ifs.is_open())
	{
		throw std::logic_error("Cannot open file!");
	}

	ifs >> numbersCount;
	numbers = new size_t[numbersCount];

	for (size_t i = 0; i < numbersCount; i++)
	{
		ifs >> numbers[i];
	}
	
	ifs.close();
}

SingletonFactory::~SingletonFactory()
{
	delete[] numbers;
}

Base* SingletonFactory::create()
{
	if (current >= numbersCount)
		return nullptr;
	else if (numbers[current++] % 2 == 0)
		return new Der1();
	else
		return new Der2();
}

SingletonFactory& SingletonFactory::getInstance()
{
	static SingletonFactory instance;
	return instance;
}
