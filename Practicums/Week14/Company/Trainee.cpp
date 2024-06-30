#include "Trainee.h"

Trainee::Trainee() : Employee(), internshipLeft(6)
{
}

Trainee::Trainee(const char* name, int age, int salary, int intershipPeriod)
	: Employee(name, age, salary), internshipLeft(intershipPeriod)
{
}

void Trainee::work()
{
	if (internshipLeft > 0)
	{
		internshipLeft--;
	}
	else
	{
		//Promote to worker
	}
}

Employee* Trainee::clone() const
{
	return new Trainee(*this);
}
