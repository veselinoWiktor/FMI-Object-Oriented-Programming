#pragma once
#include "Employee.h"

class Company
{
private:
	Employee** employees;
	size_t size;
	size_t capacity;

	void copyFrom(const Company& other);
	void moveFrom(Company&& other);
	void free();

	void resize(size_t newCap);
public:
	Company();
	Company(const Company& other);
	Company& operator=(const Company& other);
	Company(Company&& other) noexcept;
	Company& operator=(Company&& other) noexcept;
	~Company();

	void addEmployee(Employee* employee);

	size_t getSize() const;
	bool isEmpty() const;
	double getAverageSalary() const;
};

