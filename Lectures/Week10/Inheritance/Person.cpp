#include "Person.h"


void Person::copyFrom(const Person& other)
{
	name = new char[strlen(other.name) + 1];
	std::strcpy(name, other.name);
	age = other.age;
}

void Person::moveFrom(Person&& other)
{
	name = other.name;
	other.name = nullptr;
	age = other.age;
}

void Person::free()
{
	delete[] name;
}

void Person::setName(const char* newName)
{
	if (!newName || name == newName)
	{
		return;
	}

	delete[] name;
	name = new char[strlen(newName) + 1];
	strcpy(name, newName);
}

void Person::setAge(unsigned newAge)
{
	age = newAge;
}

Person::Person(const char* name, unsigned age)
{
	setName(name);
	setAge(age);
}

Person::Person(const Person& other)
{
	copyFrom(other);
}

Person::Person(Person&& other) noexcept
{
	moveFrom(std::move(other));
}

Person& Person::operator=(const Person& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Person& Person::operator=(Person&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Person::~Person()
{
	free();
}

const char* Person::getName() const
{
	return name;
}

unsigned Person::getAge() const
{
	return age;
}

void Person::print() const
{
	std::cout << name << " " << age;
}
