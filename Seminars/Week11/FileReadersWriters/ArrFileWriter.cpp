#include "ArrFileWriter.h"

ArrFileWriter::ArrFileWriter(const String& filePath) : FileWriter(filePath)
{
}

void ArrFileWriter::write(const int* arr, size_t size) const
{
	std::ofstream outFile(filePath.c_str());
	if (!outFile.is_open())
		throw std::exception("Cannot open file");

	outFile << '[';

	for (size_t i = 0; i < size - 1; i++)
		outFile << arr[i] << ' ';

	if (size - 1 >= 0)
		outFile << arr[size - 1];

	outFile << "]";
	outFile.close();
}
