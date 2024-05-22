#include <iostream>

constexpr unsigned MAX_STUDENTS = 1024;
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

struct Group {
	Student students[MAX_STUDENTS];
	double AverageGrade;
};

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

	std::cin.clear();
	std::cin.getline(firstName, NAME_MAX_LEN);
	std::cin.getline(firstName, NAME_MAX_LEN);
	std::cin.getline(lastName, NAME_MAX_LEN);
	std::cin >> facultyNumber;
	std::cin >> averageGrades;

	major = getMajorFromConsole();

	return initStudent(firstName, lastName, facultyNumber, averageGrades, major);
}

double calculateGroupAverageGrade(const Student students[MAX_STUDENTS], int groupSize)
{
	double sum = 0;
	for (int i = 0; i < groupSize; i++)
	{
		sum += students[i].averageGrade;
	}
	
	return (sum / groupSize);
}

Group createGroup(int groupSize)
{
	Group group;
	for (int i = 0; i < groupSize; i++)
	{
		Student currentStudent = initStudentFromConsole();
		group.students[i] = currentStudent;
	}

	group.AverageGrade = calculateGroupAverageGrade(group.students, groupSize);
	return group;
}

int scholarshipsCount(const Group& group, int groupSize, double minAverageGrades)
{
	int count = 0;

	for (int i = 0; i < groupSize; i++)
	{
		if (group.students[i].averageGrade >= minAverageGrades)
		{
			count++;
		}
	}

	return count;
}

void sortGroup(Group& group, int groupSize)
{
	for (int i = 0; i < groupSize - 1; i++)
	{
		int minAvgGrdIdx = i;

		for (int j = 1; j < groupSize; j++)
		{
			if (group.students[j].averageGrade < group.students[minAvgGrdIdx].averageGrade)
			{
				minAvgGrdIdx = j;
			} 
			else if ((group.students[j].averageGrade - group.students[minAvgGrdIdx].averageGrade) <= 0.0000001
				&& group.students[j].facultyNumber < group.students[minAvgGrdIdx].facultyNumber)
			{
				minAvgGrdIdx = j;
			}
		}
		
		if (minAvgGrdIdx != i)
		{
			std::swap(group.students[i], group.students[minAvgGrdIdx]);
		}
	}
}

void printGroup(const Group& group, int groupSize)
{
	for (int i = 0; i < groupSize; i++)
	{
		printStudent(group.students[i]);
	}
	std::cout << group.AverageGrade << std::endl;
}

int main()
{
    int groupSize = 0;
    std::cin >> groupSize;

	Group group = createGroup(groupSize);
	std::cout << group.AverageGrade;

	std::cout << scholarshipsCount(group, groupSize, 4.5);

	sortGroup(group, groupSize);
	printGroup(group, groupSize);
}
