#include "Cat.h"

Cat::Cat() : Animal(AnimalType::Cat)
{
}

void Cat::roar() const
{
	std::cout << "Meow meow!" << std::endl;
}

Animal* Cat::clone() const
{
	return new (std::nothrow) Cat(*this);
}
