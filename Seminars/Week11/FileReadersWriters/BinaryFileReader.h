#pragma once
#include "FileReader.h"

class BinaryFileReader : public FileReader
{
private:
	static size_t getFileSize(std::ifstream& ifs);
public:
	BinaryFileReader(const String& filePath);
	int* read(size_t& size) const override;
};

