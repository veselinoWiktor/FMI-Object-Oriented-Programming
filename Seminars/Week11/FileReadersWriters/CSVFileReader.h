#pragma once
#include "FileReader.h"

class CSVFileReader : public FileReader
{
private:
	static int getCharCount(std::ifstream& ifs, char ch);
public:
	CSVFileReader(const String& filePath);
	int* read(size_t& size) const override;
};

