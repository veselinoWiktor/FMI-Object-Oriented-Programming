#include <iostream>
#include <fstream>

constexpr int BUFFER_LENGTH = 1024;

bool myStrcmp(const char* firstStr, const char* secondStr)
{
	if (!firstStr || !secondStr)
	{
		return false;
	}

	while (*firstStr && *secondStr && *firstStr == *secondStr)
	{
		firstStr++;
		secondStr++;
	}

	return !(*firstStr - *secondStr);
}

void writeDiff(std::ifstream& before, std::ifstream& after, std::ofstream& ofs)
{
	if (!before.is_open() || !after.is_open() || !ofs.is_open())
	{
		return;
	}

	char beforeBuffer[BUFFER_LENGTH];
	char afterBuffer[BUFFER_LENGTH];

	while (!before.eof() && !after.eof())
	{
		before.getline(beforeBuffer, BUFFER_LENGTH);
		after.getline(afterBuffer, BUFFER_LENGTH);

		if (myStrcmp(beforeBuffer, afterBuffer))
		{
			ofs << beforeBuffer << std::endl;
		}
		else
		{
			if (!before.eof())
			{
				ofs << "- " << beforeBuffer << std::endl;
			}
			if (!after.eof())
			{
				ofs << "+ " << afterBuffer << std::endl;
			}
		}
		ofs.flush();
	}

	while (!before.eof())
	{
		before.getline(beforeBuffer, BUFFER_LENGTH);
		ofs << "- " << beforeBuffer << std::endl;
	}

	while (!after.eof())
	{
		after.getline(afterBuffer, BUFFER_LENGTH);
		ofs << "+ " << afterBuffer << std::endl;
	}
}

int main()
{
	std::ifstream before("file1.txt");
	std::ifstream after("file2.txt");
	std::ofstream result("result.txt");

	if (!before.is_open() || !after.is_open() || !result.is_open())
	{
		return -1;
	}

	writeDiff(before, after, result);

	before.close();
	after.close();
	result.close();
}
