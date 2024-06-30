#include "Employee.h"

void Employee::copyFrom(const Employee& other)
{
	name = new char[std::strlen(other.name) + 1];
	strcpy(name, other.name);

	salary = other.salary;
}

void Employee::moveFrom(Employee&& other)
{
	name = other.name;
	other.name = nullptr;
	salary = other.salary;
}

void Employee::free()
{
	delete[] name;
}

Employee::Employee(const char* name, double salary) : salary(salary)
{
	this->name = new char[std::strlen(name) + 1];
	strcpy(this->name, name);
}

Employee::Employee(const Employee& other)
{
	copyFrom(other);
}

Employee& Employee::operator=(const Employee& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Employee::Employee(Employee&& other) noexcept
{
	moveFrom(std::move(other));
}

Employee& Employee::operator=(Employee&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Employee::~Employee()
{
	free();
}

void Employee::print() const
{
	std::cout << "Employee";
}

size_t Employee::getWorkers() const
{
	return 0;
}

Worker* Employee::clone() const
{
	return new Employee(name, salary);
}
