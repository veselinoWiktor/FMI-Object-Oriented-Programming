#include "AnimalFactory.h"
#include "../Animals/Cat.h"
#include "../Animals/Cow.h"
#include "../Animals/Dog.h"

Animal* animalFactory(AnimalType type)
{
	switch (type)
	{
	case AnimalType::Cat:
		return new Cat();
	case AnimalType::Cow:
		return new Cow();
	case AnimalType::Dog:
		return new Dog();
	}
	return nullptr;
}
