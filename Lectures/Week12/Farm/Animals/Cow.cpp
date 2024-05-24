#include "Cow.h"

Cow::Cow() : Animal(AnimalType::Cow)
{
}

void Cow::roar() const
{
	std::cout << "Muu muu!" << std::endl;
}

Animal* Cow::clone() const
{
	return new (std::nothrow) Cow(*this);
}
