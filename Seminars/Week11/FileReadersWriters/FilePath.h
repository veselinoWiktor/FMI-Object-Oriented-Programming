#pragma once
#include "String.h"

class FilePath
{
private:
	String name;
	String extension;
public:
	FilePath(const String& fileName);
	const String& getName() const;
	const String& getExtension() const;
};

