#include "Manager.h"

void Manager::copyFrom(const Manager& other)
{
	position = new char[std::strlen(other.position) + 1];
	std::strcpy(position, other.position);

	capacity = other.capacity;
	size = other.size;
	subordinates = new Worker * [capacity];
	for (size_t i = 0; i < size; i++)
		subordinates[i] = other.subordinates[i]->clone();
}

void Manager::moveFrom(Manager&& other)
{
	position = other.position;
	other.position = nullptr;

	subordinates = other.subordinates;
	other.subordinates = nullptr;

	capacity = other.capacity;
	size = other.size;
}

void Manager::free()
{
	delete[] position;
	for (size_t i = 0; i < size; i++)
		delete subordinates[i];
	delete[] subordinates;
}

void Manager::resize(size_t newCapacity)
{
	capacity = newCapacity;
	Worker** temp = new Worker * [capacity];

	for (size_t i = 0; i < size; i++)
		temp[i] = subordinates[i];

	delete[] subordinates;
	subordinates = temp;
}

Manager::Manager(const char* name, double salary, const char* position) : Employee(name, salary), size(0), capacity(4)
{
	this->position = new char[std::strlen(position) + 1];
	strcpy(this->position, position);

	subordinates = new Worker * [capacity];
}

Manager::Manager(const Manager& other) : Employee(other)
{
	copyFrom(other);
}

Manager& Manager::operator=(const Manager& other)
{
	if (this != &other)
	{
		Employee::operator=(other);
		free();
		copyFrom(other);
	}
	return *this;
}

Manager::Manager(Manager&& other) noexcept : Employee(std::move(other))
{
	moveFrom(std::move(other));
}

Manager& Manager::operator=(Manager&& other) noexcept
{
	if (this != &other)
	{
		Employee::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Manager::~Manager()
{
	free();
}

void Manager::addSubordinate(Worker* subordinate)
{
	if (size == capacity)
		resize(capacity * 2);
	subordinates[size++] = subordinate;
}

void Manager::print() const
{
	std::cout << position << std::endl;
	for (size_t i = 0; i < size; i++)
	{
		std::cout << "\t- ";
		subordinates[i]->print();
		std::cout << " " << i << std::endl;
	}
}

size_t Manager::getWorkers() const
{
	return size;
}

Worker* Manager::clone() const
{
	return new Manager(name, salary, position);
}
