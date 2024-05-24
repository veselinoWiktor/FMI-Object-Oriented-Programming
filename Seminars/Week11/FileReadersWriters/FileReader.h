#pragma once
#include "String.h"

class FileReader
{
protected:
	String filePath;
public:
	FileReader(const String& filePath);
	virtual int* read(size_t& size) const = 0;

	virtual ~FileReader() = default;
};

