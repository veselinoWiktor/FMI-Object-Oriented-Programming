#pragma once
#include "Trainee.h"
#include "Worker.h"

class PaidTrainee : public Worker, public Trainee
{
private:
public:
	PaidTrainee();
	PaidTrainee(const char* name, int age, int salary, int internshipPeriod);

	void work() override;
	Employee* clone() const override;
};

