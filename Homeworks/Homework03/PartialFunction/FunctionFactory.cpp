#include "FunctionFactory.h"

#include "FunctionInFile.hpp"
#include "PartialFunctionByCriteria.hpp"
#include "MinimalPartialFunction.h"
#include "MaximalPartialFunction.h"


char* FunctionFactory::readStringFromBinary(std::ifstream& ifs)
{
	char buff[BUFFER_SIZE];
	ifs.getline(buff, BUFFER_SIZE, '\0');
	return buff;
}

PartialFunction* FunctionFactory::create(const String& functionFilePath)
{
	std::ifstream ifs(functionFilePath.c_str(), std::ios::binary);
	if (!ifs.is_open())
	{
		throw std::logic_error("FunctionFactory::create(); Cannot open file!");
	}

	uint16_t N = 0;
	ifs.read((char*)&N, sizeof(uint16_t));
	if (N > 32)
	{
		throw std::range_error("FunctionFactory::create(); N was out of range!");
	}

	uint16_t T = 0;
	ifs.read((char*)&T, sizeof(uint16_t));

	switch (T)
	{
	case 0:
	{
		FunctionInFile<ConstructionRules::OnlyDefinedInGivenNumbers> funcInFile(ifs, N);
		return new PartialFunctionByCriteria<FunctionInFile<ConstructionRules::OnlyDefinedInGivenNumbers>>(funcInFile);
	}
	case 1:
	{
		FunctionInFile<ConstructionRules::NotDefinedInGivenNumbers> funcInFile(ifs, N);
		return new PartialFunctionByCriteria<FunctionInFile<ConstructionRules::NotDefinedInGivenNumbers>>(funcInFile);
	}
	case 2:
	{
		FunctionInFile<ConstructionRules::DefinedForEachNumber> funcInFile(ifs, N);
		return new PartialFunctionByCriteria<FunctionInFile<ConstructionRules::DefinedForEachNumber>>(funcInFile);
	}
	case 3:
	{
		Container<PartialFunction> functions;
		for (size_t i = 0; i < N; i++)
		{
			char* buff = readStringFromBinary(ifs);
			functions.add(create(buff));
		}

		return new MaximalPartialFunction(functions);
	}
	case 4:
	{
		Container<PartialFunction> functions;
		for (size_t i = 0; i < N; i++)
		{
			char* buff = readStringFromBinary(ifs);
			functions.add(create(buff));
		}

		return new MinimalPartialFunction(functions);
	}
	default:
		throw std::logic_error("FunctionFactory::create(); T was invalid!");
		break;
	}
}