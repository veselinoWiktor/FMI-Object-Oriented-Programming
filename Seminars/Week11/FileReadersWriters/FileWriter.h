#pragma once
#include "String.h"

class FileWriter
{
protected:
	String filePath;
public:
	FileWriter(const String& filePath);
	virtual void write(const int* arr, size_t size) const = 0;

	virtual ~FileWriter() = default;
};

