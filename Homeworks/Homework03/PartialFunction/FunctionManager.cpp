#include "FunctionManager.h"
#include "FunctionInFile.hpp"
#include "PartialFunctionByCriteria.hpp"

static const char FUNCTION_FILE[] = "second.dat";

PartialFunction* FunctionManager::loadFunction(const String& functionFilePath)
{
	std::ifstream ifs(functionFilePath.c_str(), std::ios::binary);
	if (!ifs.is_open())
	{
		throw std::logic_error("FunctionManager::loadFunction(); Cannot open file!");
	}

	uint16_t N = 0;
	ifs.read((char*)&N, sizeof(uint16_t));
	if (N > 32)
	{
		throw std::range_error("FunctionManager::loadFunction(); N was out of range!");
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
	//case 3: break;
	//case 4: break;
	default:
		throw std::logic_error("FunctionManager::loadFunction(); T was invalid!");
		break;
	}
}

void FunctionManager::run()
{
	partialFunction = loadFunction(FUNCTION_FILE);
	std::cout << partialFunction->isFunctionDefinedIn(-1) << " " << partialFunction->getFunctionValue(-1) << std::endl;
	std::cout << partialFunction->isFunctionDefinedIn(0) << " " << partialFunction->getFunctionValue(0) << std::endl;
	std::cout << partialFunction->isFunctionDefinedIn(1) << " " << partialFunction->getFunctionValue(1) << std::endl;
	std::cout << partialFunction->isFunctionDefinedIn(2) << " " << partialFunction->getFunctionValue(2) << std::endl;
	std::cout << partialFunction->isFunctionDefinedIn(3) << " " << partialFunction->getFunctionValue(3) << std::endl;
	std::cout << partialFunction->isFunctionDefinedIn(4) << " " << partialFunction->getFunctionValue(4) << std::endl;
	std::cout << partialFunction->isFunctionDefinedIn(5) << " " << partialFunction->getFunctionValue(5) << std::endl;
	std::cout << partialFunction->isFunctionDefinedIn(6) << " " << partialFunction->getFunctionValue(6) << std::endl;
	std::cout << partialFunction->isFunctionDefinedIn(7) << " " << partialFunction->getFunctionValue(7) << std::endl;
	std::cout << partialFunction->isFunctionDefinedIn(8) << " " << partialFunction->getFunctionValue(8) << std::endl;
	std::cout << partialFunction->isFunctionDefinedIn(9) << " " << partialFunction->getFunctionValue(9) << std::endl;
	std::cout << partialFunction->isFunctionDefinedIn(10) << " " << partialFunction->getFunctionValue(10) << std::endl;

}
