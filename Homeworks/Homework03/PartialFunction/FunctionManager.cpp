#include "FunctionManager.h"
#include "FunctionFactory.h"

constexpr int64_t CURRENTX_MAX = 2147483648i64;

//Currently working by changing the initial function filePath from here
static const char FUNCTION_FILE[] = "func.dat";

void FunctionManager::printInInterval() const
{
	int a = 0;
	int b = 0;

	std::cout << "Enter interval start: ";

	std::cin >> a;
	std::cout << "Enter interval end: ";
	std::cin >> b;

	for (int i = a; i <= b; i++)
	{
		if (partialFunction->isFunctionDefinedIn(i))
		{
			std::cout << "f(" << i << ") = " << partialFunction->getFunctionValue(i) << std::endl;
		}
	}
}

void FunctionManager::printPointByPoint() const
{
	char continueLoop = '\0';
	int64_t currentX = INT32_MIN;

	std::cout << "Enter: 1 - To display the first defined point." << std::endl;
	std::cout << '>';
	std::cin >> continueLoop;

	while (continueLoop == '1')
	{
		for (currentX; currentX <= INT32_MAX; currentX++)
		{
			if (partialFunction->isFunctionDefinedIn(currentX))
			{
				std::cout << "f(" << currentX << ") = " << partialFunction->getFunctionValue(currentX) << std::endl;
				currentX++;
				break;
			}
		}

		if (currentX == CURRENTX_MAX)
		{
			std::cout << "No more defined points in the function!" << std::endl;
			break;
		}

		std::cout << "Enter: 1 - To display the next defined point." << std::endl;
		std::cout << '>';
		std::cin >> continueLoop;
	} 
}

void FunctionManager::run()
{
	partialFunction = FunctionFactory::create(FUNCTION_FILE);

	std::cout << "Choose function display mode:" << std::endl;
	std::cout << "Enter: 1 - To display the function in given interval." << std::endl;
	std::cout << "Enter: 2 - To display the function point by point." << std::endl;
	std::cout << '>';

	int promptRes = 0;
	std::cin >> promptRes;
	switch (promptRes)
	{
	case 1:
		printInInterval();
		
		break;
	case 2:
		printPointByPoint();
		break;
	default:
		break;
	}
}
