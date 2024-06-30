#pragma once
#include "PaidTrainee.h"
#include "Worker.h"
#include "Trainee.h"

enum class EmployeeType
{
	Worker,
	Trainee,
	PaidTrainee
};

class CompanyFactory
{
private:
	static Worker* createWorker();
	static Trainee* createTrainee();
	static PaidTrainee* createPaidTrainee();
public:
	static Employee* createEmployee(EmployeeType type);
};

