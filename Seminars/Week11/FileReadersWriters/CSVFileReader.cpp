#include "CSVFileReader.h"

int CSVFileReader::getCharCount(std::ifstream& ifs, char ch)
{
	size_t currPos = ifs.tellg();

	int count = 0;
	while (true)
	{
		char current = ifs.get();

		if (ifs.eof())
		{
			break;
		}

		if (current == ch)
		{
			count++;
		}
	}

	ifs.clear();
	ifs.seekg(currPos);
	return count;
}
