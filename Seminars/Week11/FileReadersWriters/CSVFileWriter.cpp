#include "CSVFileWriter.h"

CSVFileWriter::CSVFileWriter(const String& filePath) : FileWriter(filePath)
{
}

void CSVFileWriter::write(const int* arr, size_t size) const
{
	std::ofstream outFile(filePath.c_str());

	if (!outFile.is_open())
	{
		throw std::exception("Cannot open file!");
	}

	for (size_t i = 0; i < size - 1; i++)
	{
		outFile << arr[i] << ',';
	}

	outFile << arr[size - 1];
	outFile.close();
}
