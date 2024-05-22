#include "NewLinesCount.h"

unsigned getCharCountFromFile(std::ifstream& ifs, char ch)
{
	if (!ifs.is_open())
	{
		return 0;
	}

	unsigned count = 0;
	while (!ifs.eof())
	{
		char current = ifs.get();

		if (current == ch)
		{
			count++;
		}
	}

	return count;
}

unsigned getLinesCount(const char* filename)
{
	std::ifstream myFile(filename);

	if (!myFile.is_open())
	{
		return 0;
	}

	return getCharCountFromFile(myFile, '\n') + 1;
}

