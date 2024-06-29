#pragma once
#include "PartialFunction.h"
#include "String.h"

class FunctionManager
{
private:
	PartialFunction* partialFunction = nullptr;

	void printInInterval() const;
	void printPointByPoint() const;
public:
	FunctionManager() = default;
	//Might want to add if we want the filePath to be flexible
	//FunctionManager(const String& functionFilePath);
	//FunctionManager(const PartialFunction& partialFunction);
	FunctionManager(const FunctionManager& other) = delete;
	FunctionManager& operator=(const FunctionManager& other) = delete;
	~FunctionManager();

	void run();
};

