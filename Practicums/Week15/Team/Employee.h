#pragma once
#include <iostream>
#include "Worker.h"
#pragma warning(disable:4996)

class Employee : public Worker
{
protected:
	char* name;
	double salary;
private:
	void copyFrom(const Employee& other);
	void moveFrom(Employee&& other);
	void free();
public:
	Employee(const char* name, double salary);
	Employee(const Employee& other);
	Employee& operator=(const Employee& other);
	Employee(Employee&& other) noexcept;
	Employee& operator=(Employee&& other) noexcept;
	~Employee();

	void print() const override;
	size_t getWorkers() const override;
	Worker* clone() const override;
};

