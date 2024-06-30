#pragma once
#include <iostream>
#pragma warning (disable: 4996)

class Employee
{
protected:
	char* name;
	int age;
	double salary;

	void copyFrom(const Employee& other);
	void moveFrom(Employee&& other);
	void free();

	void setName(const char* name);
	void setAge(int age);
	void setSalary(double salary);
public:
	Employee();
	Employee(const char* name, int age, double salary);
	Employee(const Employee& other);
	Employee& operator=(const Employee& other);
	Employee(Employee&& other) noexcept;
	Employee& operator=(Employee&& other) noexcept;
	virtual ~Employee();

	const char* getName() const;
	int getAge() const;
	double getSalary() const;

	virtual void work() = 0;

	virtual Employee* clone() const = 0;
};

