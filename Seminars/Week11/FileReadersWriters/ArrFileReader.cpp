#include "ArrFileReader.h"

int ArrFileReader::getCharCount(std::ifstream& ifs, char ch)
{
	size_t currPos = ifs.tellg();

	int count = 0;
	while (true)
	{
		char current = ifs.get();
		if (ifs.eof())
			break;

		if (current == ch)
			count++;
	}

	ifs.clear(); //clear from the eof flag
	ifs.seekg(currPos);
	return count;
}

ArrFileReader::ArrFileReader(const String& filePath) : FileReader(filePath)
{

}

int* ArrFileReader::read(size_t& size) const
{
	std::ifstream inFile(filePath.c_str());
	if (!inFile.is_open())
		throw std::exception("File not opened!");

	size = getCharCount(inFile, ' ') + 1;
	int* arr = new int[size];

	inFile.ignore();

	for (size_t i = 0; i < size; i++)
		inFile >> arr[i];

	inFile.close();
	return arr;
}
