#pragma once
#include "Employee.h"

class Worker : virtual public Employee
{
protected:
	int workMonths = 0;
public:
	Worker();
	Worker(const char* name, int age, double salary);

	void work() override;
	int getWorkMonths() const;

	Employee* clone() const override;
};

