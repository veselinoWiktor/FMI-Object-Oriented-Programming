#pragma once
#include <iostream>

enum class AnimalType
{
	Dog,
	Cat,
	Cow
};

class Animal
{
private:
	AnimalType type;
public:
	Animal(AnimalType type);
	virtual void roar() const = 0;
	virtual Animal* clone() const = 0;
	virtual ~Animal() = default;

	AnimalType getType() const
	{
		return type;
	}
};

