#pragma once
#include "Employee.h"

class Trainee : virtual public Employee
{
protected:
	int internshipLeft;
public:
	Trainee();
	Trainee(const char* name, int age, int salary, int intershipPeriod);

	void work() override;
	Employee* clone() const override;
};

