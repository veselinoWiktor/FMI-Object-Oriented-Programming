#include "PaidTrainee.h"
#include "Company.h"
#include "CompanyFactory.h"

#include <iostream>

int main()
{
	Company company;

	company.addEmployee(CompanyFactory::createEmployee(EmployeeType::Worker));
	company.addEmployee(CompanyFactory::createEmployee(EmployeeType::Trainee));
	company.addEmployee(CompanyFactory::createEmployee(EmployeeType::Trainee));
	/*company.addEmployee(CompanyFactory::createEmployee(EmployeeType::Worker));
	company.addEmployee(CompanyFactory::createEmployee(EmployeeType::PaidTrainee));
	company.addEmployee(CompanyFactory::createEmployee(EmployeeType::Worker));*/

	Company c2(company);

	std::cout << c2.getAverageSalary() << std::endl;
}