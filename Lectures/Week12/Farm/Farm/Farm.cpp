#include "Farm.h"

void Farm::copyFrom(const Farm& other)
{
	capacity = other.capacity;
	animalsCount = other.animalsCount;
	animals = new Animal * [capacity];

	for (size_t i = 0; i < animalsCount; i++)
	{
		Animal* cloned = other.animals[i]->clone();
		if (cloned)
		{
			animals[i] = cloned;
		}
	}

}

void Farm::moveFrom(Farm&& other)
{
	capacity = other.capacity;
	animalsCount = other.animalsCount;
	animals = other.animals;
	other.animals = nullptr;
}

void Farm::free()
{
	for (size_t i = 0; i < animalsCount; i++)
	{
		delete animals[i];
	}
	delete[] animals;
}

void Farm::resize(size_t newCapacity)
{
	capacity = newCapacity;
	Animal** temp = new Animal * [capacity] {nullptr};
	for (size_t i = 0; i < animalsCount; i++)
	{
		temp[i] = animals[i];
	}
	delete[] animals;
	animals = temp;
}

Farm::Farm() : animalsCount(0), capacity(16)
{
	animals = new Animal * [capacity];
}

Farm::Farm(const Farm& other)
{
	copyFrom(other);
}

Farm::Farm(Farm&& other) noexcept
{
	moveFrom(std::move(other));
}

Farm& Farm::operator=(const Farm& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Farm& Farm::operator=(Farm&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Farm::~Farm()
{
	free();
}

void Farm::addAnimal(AnimalType animalType)
{
	if (animalsCount == capacity)
	{
		resize(capacity * 2);
	}
	animals[animalsCount++] = animalFactory(animalType);
}

void Farm::addAnimal(const Animal& animal)
{
	if (capacity == animalsCount)
	{
		resize(2 * capacity);
	}
	animals[animalsCount++] = animal.clone();
}

void Farm::roarAll() const
{
	for (size_t i = 0; i < animalsCount; i++)
	{
		animals[i]->roar();
	}
}

AnimalType Farm::getTypeByIndex(size_t index) const
{
	if (index >= animalsCount)
	{
		throw std::out_of_range("Invalid index!");
	}
	return animals[index]->getType();
}
