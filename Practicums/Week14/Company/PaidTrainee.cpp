#include "PaidTrainee.h"

PaidTrainee::PaidTrainee() : Employee(), Worker(), Trainee()
{
}

PaidTrainee::PaidTrainee(const char* name, int age, int salary, int internshipPeriod)
	: Employee(name, age, salary), Worker(name, age, salary), Trainee(name, age, salary, internshipPeriod)
{
}

void PaidTrainee::work()
{
	if (internshipLeft > 0)
	{
		internshipLeft--;
		workMonths++;
	}
	else
	{
		//promote to worker
	}
}

Employee* PaidTrainee::clone() const
{
	return new PaidTrainee(*this);
}
