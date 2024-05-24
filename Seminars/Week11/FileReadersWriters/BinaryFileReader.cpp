#include "BinaryFileReader.h"

size_t BinaryFileReader::getFileSize(std::ifstream& ifs)
{
	size_t currPos = ifs.tellg();
	ifs.seekg(std::ios::end);
	size_t result = ifs.tellg();
	ifs.seekg(currPos);
	return result;
}

BinaryFileReader::BinaryFileReader(const String& filePath) : FileReader(filePath)
{
}

int* BinaryFileReader::read(size_t& size) const
{
	std::ifstream inFile(filePath.c_str(), std::ios::binary);
	if (!inFile.is_open())
	{
		throw std::exception("File not opened!");
	}

	size = getFileSize(inFile) / sizeof(int);
	int* arr = new int[size];

	inFile.read((char*)arr, size * sizeof(int));

	inFile.close();
	return arr;
}


