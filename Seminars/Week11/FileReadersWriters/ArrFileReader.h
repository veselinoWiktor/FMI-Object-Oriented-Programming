#pragma once
#include "FileReader.h"

class ArrFileReader : public FileReader
{
private:
	static int getCharCount(std::ifstream& ifs, char ch);
public:
	ArrFileReader(const String& filePath);
	int* read(size_t& size) const override;
};

