#include <iostream>
#include <fstream>

namespace FileNamesConstants
{
	constexpr char INPUT_FILE_NAME[] = "inputFileNumbers.dat";
	constexpr char EVEN_FILE_NAME[] = "evenNumbers.dat";
	constexpr char ODD_FILE_NAME[] = "oddNumbers.dat";
}

struct FileContents
{
	int* contents = nullptr;
	size_t contentSize = 0;
};

unsigned getFileSize(std::ifstream& ifs)
{
	unsigned currentPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	unsigned result = ifs.tellg();
	ifs.seekg(currentPos, std::ios::beg);
	return result;
}

FileContents readDataFromFile(std::ifstream& ifs)
{
	FileContents contents;
	size_t fileSize = getFileSize(ifs);
	contents.contentSize = fileSize / sizeof(int);
	contents.contents = new int[contents.contentSize];

	for (size_t i = 0; i < contents.contentSize; i++)
	{
		ifs.read((char*)&contents.contents[i], sizeof(int));
	}

	return contents;
}

void freeFileContents(FileContents& fileContents)
{
	delete[] fileContents.contents;
	fileContents.contentSize = 0;
}

size_t countEvenNumbers(const int* numbers, size_t size)
{
	size_t evenCounter = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (!(numbers[i] & 1))
		{
			evenCounter++;
		}
	}

	return evenCounter;
}

void fillEvenOddArrays(const FileContents& inputContent, int* even, int* odd)
{
	size_t evenIndex = 0;
	size_t oddIndex = 0;
	for (size_t i = 0; i < inputContent.contentSize; i++)
	{
		if (!(inputContent.contents[i] & 1))
		{
			even[evenIndex++] = inputContent.contents[i];
		}
		else
		{
			odd[oddIndex++] = inputContent.contents[i];
		}
	}
}

void divideOddAndEven(const char* sourceFile, const char* evenFile, const char* oddFile)
{
	std::ifstream input(sourceFile, std::ios::binary);
	if (!input.is_open())
	{
		std::cout << "Error while opening input file." << std::endl;
		return;
	}

	std::ofstream even(evenFile, std::ios::binary);
	if (!even.is_open())
	{
		input.close();
		std::cout << "Error while opening even file." << std::endl;
		return;
	}

	std::ofstream odd(oddFile, std::ios::binary);
	if (!odd.is_open())
	{
		input.close();
		even.close();
		std::cout << "Error while opening odd file." << std::endl;
		return;
	}

	FileContents inputFileContents = readDataFromFile(input);
	input.close();

	size_t evenCount = countEvenNumbers(inputFileContents.contents, inputFileContents.contentSize);
	size_t oddCount = inputFileContents.contentSize - evenCount;

	int* evenNumbers = new int[evenCount];
	int* oddNumbers = new int[oddCount];

	fillEvenOddArrays(inputFileContents, evenNumbers, oddNumbers);

	even.write((const char*)evenNumbers, evenCount * sizeof(int));
	odd.write((const char*)oddNumbers, oddCount * sizeof(int));

	delete[] evenNumbers;
	delete[] oddNumbers;

	freeFileContents(inputFileContents);
	even.close();
	odd.close();
}

int main()
{
	divideOddAndEven(
		FileNamesConstants::INPUT_FILE_NAME,
		FileNamesConstants::EVEN_FILE_NAME,
		FileNamesConstants::ODD_FILE_NAME
	);
	return 0;
}
