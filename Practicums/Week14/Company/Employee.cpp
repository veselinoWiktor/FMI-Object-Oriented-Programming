#include "Employee.h"

void Employee::copyFrom(const Employee& other)
{
	age = other.age;
	salary = other.salary;

	name = new char[std::strlen(other.name) + 1];
	std::strcpy(name, other.name);
}

void Employee::moveFrom(Employee&& other)
{
	age = other.age;
	salary = other.salary;

	name = other.name;
	other.name = nullptr;
}

void Employee::free()
{
	delete[] name;
}

void Employee::setName(const char* name)
{
	if (name && this->name != name)
	{
		free();
		this->name = new char[std::strlen(name) + 1];
		std::strcpy(this->name, name);
	}
}

void Employee::setAge(int age)
{
	if (age >= 16 && age <= 70)
		this->age = age;
}

void Employee::setSalary(double salary)
{
	this->salary = salary;
}

Employee::Employee()
{
	setName("");
	setAge(0);
	setSalary(0);
}

Employee::Employee(const char* name, int age, double salary)
{
	setName(name);
	setAge(age);
	setSalary(salary);
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

const char* Employee::getName() const
{
	return name;
}

int Employee::getAge() const
{
	return age;
}

double Employee::getSalary() const
{
	return salary;
}
