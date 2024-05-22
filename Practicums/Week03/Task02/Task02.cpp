#include <iostream>
#include <fstream>
#include <sstream>

namespace Constants {
	constexpr int MAX_GROUP_SIZE = 1024;
	constexpr int MAX_NAME_SIZE = 16;
	constexpr int MAX_BUFF_SIZE = 1024;
	const char fileName[] = "studentsGroup.csv";
}

enum class HairColor
{
	Brown = 0,
	Black,
	Blonde,
	Red,
	White
};

struct Student
{
	char firstName[Constants::MAX_NAME_SIZE];
	char lastName[Constants::MAX_NAME_SIZE];
	int fn;
	double avgGrade;
	HairColor hairColor;
};

struct Group
{
	Student students[Constants::MAX_GROUP_SIZE];
	size_t groupSize;
};

void saveHairColor(std::ofstream& ofs, const HairColor& hairColor)
{
	switch (hairColor)
	{
	case HairColor::Brown: ofs << "Brown"; break;
	case  HairColor::Black: ofs << "Black"; break;
	case HairColor::Blonde: ofs << "Blonde"; break;
	case HairColor::Red: ofs << "Red"; break;
	case HairColor::White: ofs << "White"; break;
	default:
		break;
	}
}

void saveStudent(std::ofstream& ofs, const Student& student)
{
	ofs << student.firstName << ','
		<< student.lastName << ','
		<< student.fn << ','
		<< student.avgGrade << ',';
	saveHairColor(ofs, student.hairColor);
	ofs << std::endl;
}

void saveGroup(const char fileName[], const Group& group)
{
	if (!fileName)
	{
		return;
	}

	std::ofstream ofs(fileName);
	if (!ofs.is_open())
	{
		return;
	}

	for (size_t i = 0; i < group.groupSize; i++)
	{
		saveStudent(ofs, group.students[i]);
	}
	
	ofs.close();
}

int findGroupSize(std::ifstream& ifs)
{
	ifs.seekg(0, std::ios::end);
	std::cout << ifs.tellg() << std::endl;
	int result = ifs.tellg() / sizeof(Student);
	ifs.seekg(0, std::ios::beg);
	return result;
}

HairColor loadHairColor(char hairColor[])
{
	if (!strcmp(hairColor, "Brown"))
	{
		return HairColor::Brown;
	}
	else if (!strcmp(hairColor, "Black"))
	{
		return HairColor::Black;
	}
	else if (!strcmp(hairColor, "Blonde"))
	{
		return HairColor::Blonde;
	}
	else if (!strcmp(hairColor, "Red"))
	{
		return HairColor::Red;
	}
	else if (!strcmp(hairColor, "White"))
	{
		return HairColor::White;
	}
}

Student loadStudent(char studentLine[])
{
	Student st{};
	std::stringstream ss(studentLine);

	ss.getline(st.firstName, Constants::MAX_NAME_SIZE, ',');
	ss.getline(st.lastName, Constants::MAX_NAME_SIZE, ',');
	ss >> st.fn;
	ss.get();
	ss >> st.avgGrade;
	ss.get();
	char hairColor[Constants::MAX_BUFF_SIZE];
	ss.getline(hairColor, Constants::MAX_BUFF_SIZE, '\n');
	st.hairColor = loadHairColor(hairColor);

	return st;
}

Group loadGroup(const char fileName[])
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		return {};
	}

	Group group{};
	char buff[Constants::MAX_BUFF_SIZE];
	while (!ifs.eof())
	{
		ifs.getline(buff, Constants::MAX_BUFF_SIZE);
		group.students[group.groupSize++] = loadStudent(buff);
	}

	ifs.close();
}

int main()
{
	Student st1{ "viktor", "veselinov", 10000, 5.6, HairColor::Blonde };
	Student st2{ "Desi", "Daneva", 12312, 6.0, HairColor::Brown };

	Group grp;
	grp.groupSize = 2;
	grp.students[0] = st1;
	grp.students[1] = st2;

	saveGroup(Constants::fileName, grp);

	loadGroup(Constants::fileName);
}
