#pragma once
#include "../Animals/Animal.h"
#include "../Factory/AnimalFactory.h"

class Farm
{
private:
	Animal** animals;
	size_t animalsCount;
	size_t capacity;

	void copyFrom(const Farm& other);
	void moveFrom(Farm&& other);
	void free();

	void resize(size_t newCapacity);
public:
	Farm();
	Farm(const Farm& other);
	Farm(Farm&& other) noexcept;
	Farm& operator=(const Farm& other);
	Farm& operator=(Farm&& other) noexcept;
	~Farm();

	void addAnimal(AnimalType animalType);
	void addAnimal(const Animal& animal);
	void roarAll() const;

	AnimalType getTypeByIndex(size_t index) const;
};

