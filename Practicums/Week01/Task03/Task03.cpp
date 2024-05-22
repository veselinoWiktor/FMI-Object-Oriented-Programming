#include <iostream>

constexpr int NAME_MAX_LEN = 17;
constexpr int MAX_LEN = 1024;

enum class Major {
	Informatics = 0,
	InformaticSystems,
	ComputerScience,
	SoftwareEngineering,
	DataAnalisys,
	Mathematics,
	Statistics,
	Error
};

struct Student {
	char firstName[17];
	char lastName[17];
	unsigned facultyNumber;
	double averageGrade;
	Major major;
};

void printMajor(const Major& major)
{
	switch (major)
	{
	case Major::Informatics: std::cout << "Informatics"; break;
	case Major::InformaticSystems: std::cout << "Informatic Systems"; break;
	case Major::ComputerScience: std::cout << "Computer Science"; break;
	case Major::SoftwareEngineering: std::cout << "Software Engineering"; break;
	case Major::DataAnalisys: std::cout << "Data Analisys"; break;
	case Major::Mathematics: std::cout << "Mathematics"; break;
	case Major::Statistics: std::cout << "Statistics"; break;
	case Major::Error: std::cout << "Error"; break;
	}
}

void printStudent(const Student& student)
{
	std::cout << "First name is: " << student.firstName << std::endl
		<< "Last name is: " << student.lastName << std::endl
		<< "Faculty number: " << student.facultyNumber << std::endl
		<< "Average grades: " << student.averageGrade << std::endl
		<< "Major: ";
	printMajor(student.major);
	std::cout << std::endl;
}

void myStrcpy(const char* source, char* destination)
{
	if (!destination || !source)
	{
		return;
	}

	while (*source)
	{
		*destination = *source;
		destination++;
		source++;
	}

	*destination = '\0';
}

int myStrcmp(const char* first, const char* second)
{
	if (!first || !second)
	{
		return INT16_MIN;
	}

	while ((*first) && (*second) && ((*first) == (*second)))
	{
		first++;
		second++;
	}

	return (*first - *second);
}

Major getMajorFromConsole()
{
	char major[MAX_LEN];
	std::cin.clear();
	std::cin.getline(major, MAX_LEN);
	std::cin.getline(major, MAX_LEN);

	if (!myStrcmp(major, "Informatics"))
		return Major::Informatics;
	else if (!myStrcmp(major, "Informatic Systems"))
		return Major::InformaticSystems;
	else if (!myStrcmp(major, "Computer Science"))
		return Major::ComputerScience;
	else if (!myStrcmp(major, "Software Engineering"))
		return Major::SoftwareEngineering;
	else if (!myStrcmp(major, "Data Analisys"))
		return Major::Mathematics;
	else if (!myStrcmp(major, "Mathematics"))
		return Major::Mathematics;
	else if (!myStrcmp(major, "Statistics"))
		return Major::Statistics;
	else
		return Major::Error;
}

Student initStudent(const char* firstName, const char* lastName, int facultyNumber, double averageGrade, Major major)
{
	Student student;
	if (firstName)
		myStrcpy(firstName, student.firstName);

	if (lastName)
		myStrcpy(lastName, student.lastName);

	if (facultyNumber >= 10000 && facultyNumber <= 99999)
	{
		student.facultyNumber = facultyNumber;
	}
	else
	{
		student.facultyNumber = 0;
	}

	if (averageGrade >= 2 && averageGrade <= 6)
		student.averageGrade = averageGrade;

	student.major = major;
	return student;
}

Student initStudentFromConsole()
{
	char firstName[NAME_MAX_LEN];
	char lastName[NAME_MAX_LEN];
	unsigned facultyNumber;
	double averageGrades;
	Major major;

	std::cin.getline(firstName, NAME_MAX_LEN);
	std::cin.getline(lastName, NAME_MAX_LEN);
	std::cin >> facultyNumber;
	std::cin >> averageGrades;

	major = getMajorFromConsole();

	return initStudent(firstName, lastName, facultyNumber, averageGrades, major);
}

int main()
{
	char firstName[] = "Pesho";
	char secondName[] = "Goshev";
	Student std = initStudent(firstName, secondName, 31243, 5.7, Major::SoftwareEngineering);
	printStudent(std);

	Student secondStd = initStudentFromConsole();
	printStudent(secondStd);
}
