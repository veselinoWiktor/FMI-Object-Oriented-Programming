#include "CompanyFactory.h"

Worker* CompanyFactory::createWorker()
{
	char name[1024];
	std::cout << "Enter name: " << std::endl;
	std::cin >> name;

	int age;
	std::cout << "Enter age: " << std::endl;;
	std::cin >> age;

	double salary;
	std::cout << "Enter salary: " << std::endl;
	std::cin >> salary;

	return new Worker(name, age, salary);
}

Trainee* CompanyFactory::createTrainee()
{
	char name[1024];
	std::cout << "Enter name: " << std::endl;
	std::cin >> name;

	int age;
	std::cout << "Enter age: " << std::endl;;
	std::cin >> age;

	double salary;
	std::cout << "Enter salary: " << std::endl;
	std::cin >> salary;

	int intershipMonths;
	std::cout << "Enter internship months: " << std::endl;
	std::cin >> intershipMonths;

	return new Trainee(name, age, salary, intershipMonths);
}

PaidTrainee* CompanyFactory::createPaidTrainee()
{
	char name[1024];
	std::cout << "Enter name: " << std::endl;
	std::cin >> name;

	int age;
	std::cout << "Enter age: " << std::endl;;
	std::cin >> age;

	double salary;
	std::cout << "Enter salary: " << std::endl;
	std::cin >> salary;

	int intershipMonths;
	std::cout << "Enter internship months: " << std::endl;
	std::cin >> intershipMonths;

	return new PaidTrainee(name, age, salary, intershipMonths);
}

Employee* CompanyFactory::createEmployee(EmployeeType type)
{
	switch (type)
	{
	case EmployeeType::Worker:
		return createWorker();
		break;
	case EmployeeType::Trainee:
		return createTrainee();
		break;
	case EmployeeType::PaidTrainee:
		return createPaidTrainee();
		break;
	}
}
