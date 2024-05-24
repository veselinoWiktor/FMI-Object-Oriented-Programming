#pragma once
#include "FileWriter.h"

class CSVFileWriter : public FileWriter
{
public:
	CSVFileWriter(const String& filePath);
	void write(const int* arr, size_t size) const override;
};

