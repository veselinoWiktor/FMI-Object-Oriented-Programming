#include "Singleton.h"

Singleton::Singleton()
{
	std::cout << "Singleton::Singleton()" << std::endl;
}

Singleton::~Singleton()
{
	std::cout << "Singleton::~Singleton()" << std::endl;
}

Singleton& Singleton::getInstance()
{
	static Singleton instance;
	return instance;
}

void Singleton::doStuff() const
{
	std::cout << this << std::endl;
}
