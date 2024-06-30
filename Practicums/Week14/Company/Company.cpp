#include "Company.h"

void Company::copyFrom(const Company& other)
{
	size = other.size;
	capacity = other.capacity;

	employees = new Employee * [capacity];
	for (size_t i = 0; i < size; i++)
		employees[i] = other.employees[i]->clone();
}

void Company::moveFrom(Company&& other)
{
	employees = other.employees;
	other.employees = nullptr;
}

void Company::free()
{
	for (size_t i = 0; i < size; i++)
	{
		delete employees[i];
	}
	delete[] employees;
}

void Company::resize(size_t newCap)
{
	capacity = newCap;

	Employee** temp = new Employee * [capacity];
	for (size_t i = 0; i < size; i++)
		temp[i] = employees[i];

	delete[] employees;
	employees = temp;
}

Company::Company() : size(0), capacity(4)
{
	employees = new Employee * [capacity];
}

Company::Company(const Company& other)
{
	copyFrom(other);
}

Company& Company::operator=(const Company& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Company::Company(Company&& other) noexcept
{
	moveFrom(std::move(other));
}

Company& Company::operator=(Company&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Company::~Company()
{
	free();
}

void Company::addEmployee(Employee* employee)
{
	if (size == capacity)
	{
		resize(capacity * 2);
	}

	employees[size++] = employee;
}

size_t Company::getSize() const
{
	return size;
}

bool Company::isEmpty() const
{
	return size == 0;
}

double Company::getAverageSalary() const
{
	if (isEmpty())
	{
		throw std::exception("...");
	}

	double res = 0;
	for (size_t i = 0; i < size; i++)
	{
		res += employees[i]->getSalary();
	}
	return res / size;
}
