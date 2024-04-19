#include "MultiSet.h"
#include <iostream>
#include <fstream>

void MultiSet::copyFrom(const MultiSet& other)
{
	maxNumber = other.maxNumber;
	numberBits = other.numberBits;
	bucketsCount = other.bucketsCount;

	data = new char[bucketsCount];
	for (size_t i = 0; i < bucketsCount; i++)
	{
		data[i] = other.data[i];
	}
}

void MultiSet::free()
{
	delete[] data;
	data = nullptr;
	bucketsCount = numberBits = maxNumber = 0;
}

size_t MultiSet::getBucket(unsigned num) const
{
	return (num * numberBits) / MultiSetConstants::BITS_IN_BYTE;
}

size_t MultiSet::getPosition(unsigned num) const
{
	return (num * numberBits) % MultiSetConstants::BITS_IN_BYTE;
}

size_t MultiSet::bucketsNeeded(size_t num) const
{
	size_t result = (maxNumber * numberBits) / MultiSetConstants::BITS_IN_BYTE;
	if ((maxNumber + 1) % MultiSetConstants::BITS_IN_BYTE != 0)
		result++;

	return result;
}

char MultiSet::getMask(unsigned position) const
{
	return 1 << (MultiSetConstants::LAST_BIT_INDEX - position);
}

void MultiSet::setMaxNumber(size_t _maxNumber)
{
	maxNumber = _maxNumber;
}

void MultiSet::setNumberBits(size_t _numberBits)
{
	if (MultiSetConstants::MIN_BITS_FOR_NUMBER <= _numberBits
		&& _numberBits <= MultiSetConstants::MAX_BITS_FOR_NUMBER)
	{
		numberBits = _numberBits;
	}
	//TODO might need to throw exception
}

void MultiSet::initData()
{
	bucketsCount = bucketsNeeded(maxNumber);

	data = new char[bucketsCount];

	for (size_t i = 0; i < bucketsCount; i++)
	{
		data[i] = 0;
	}
}

void MultiSet::printBucketMemory(unsigned bucketIdx) const
{
	unsigned upperBound = MultiSetConstants::BITS_IN_BYTE;

	if (bucketIdx == bucketsCount - 1)
	{
		unsigned lastNumEndPos = getPosition(maxNumber + 1);
		upperBound = (lastNumEndPos == 0) ? upperBound : lastNumEndPos;
	}

	bool bitVal = 0;
	for (size_t i = 0; i < upperBound; i++)
	{
		bitVal = data[bucketIdx] & getMask(i);

		if (bitVal)
			std::cout << "1";
		else
			std::cout << "0";
	}
}

MultiSet::MultiSet(size_t n, size_t k)
{
	setNumberBits(k);
	setMaxNumber(n);
	initData();
}

MultiSet::MultiSet(const MultiSet& other)
{
	copyFrom(other);
}

MultiSet& MultiSet::operator=(const MultiSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

MultiSet::~MultiSet()
{
	free();
}

size_t MultiSet::getBitsPerNumber() const
{
	return numberBits;
}

size_t MultiSet::getMaxNumber() const
{
	return maxNumber;
}

void MultiSet::addNumber(unsigned num)
{
	if (num > maxNumber)
	{
		throw std::out_of_range("Num is above the range of the set");
	}

	if (containsCount(num) == powerOfTwo(numberBits) - 1)
	{
		throw std::logic_error("Num already have max value");
	}

	int numBucket = getBucket(num);
	int numPosition = getPosition(num);

	if ((numPosition + numberBits) > MultiSetConstants::BITS_IN_BYTE)
	{
		numPosition = ((numPosition + numberBits) - MultiSetConstants::BITS_IN_BYTE) - 1;
		numBucket++;
	}
	else
	{
		numPosition += (numberBits - 1);
	}

	for (size_t i = 0; i < numberBits; i++)
	{
		char mask = getMask(numPosition);
		bool bitVal = data[numBucket] & mask;

		if (!bitVal)
		{
			data[numBucket] |= mask;
			break;
		}
		else
		{
			data[numBucket] &= ~mask;
			if (numPosition == MultiSetConstants::FIRST_BIT_INDEX) {
				numPosition = MultiSetConstants::LAST_BIT_INDEX;
				numBucket--;
			}
			else
			{
				numPosition--;
			}
		}
	}
}

unsigned MultiSet::containsCount(unsigned num) const
{
	if (num > maxNumber)
	{
		throw std::out_of_range("Num is above the range of the set");
	}

	int numBucket = getBucket(num);
	int numPosition = getPosition(num);

	int numCount = 0;
	for (size_t i = 0; i < numberBits; i++)
	{
		char mask = getMask(numPosition);
		bool bitVal = data[numBucket] & mask;

		numCount |= bitVal;
		numCount <<= 1;

		if (numPosition == MultiSetConstants::LAST_BIT_INDEX)
		{
			numPosition = MultiSetConstants::FIRST_BIT_INDEX;
			numBucket++;
		}
		else
		{
			numPosition++;
		}
	}

	return numCount >> 1;
}

void MultiSet::print() const
{
	unsigned currNumCount = 0;
	for (size_t i = 0; i <= maxNumber; i++)
	{
		currNumCount = containsCount(i);
		if (currNumCount > 0)
		{
			std::cout << i << " is contained: " << currNumCount << "times." << std::endl;
		}
	}
}

void MultiSet::printMemory() const
{
	for (size_t i = 0; i < bucketsCount; i++)
	{
		printBucketMemory(i);
		std::cout << " ";
	}
	std::cout << std::endl;
}

void MultiSet::serialize(const char* filename) const
{
	if (!filename)
	{
		throw std::invalid_argument("Filename was nullptr.");
	}

	std::ofstream ofs(filename, std::ios::binary);
	if (!ofs.is_open())
	{
		throw std::runtime_error("Stream is already opened.");
	}

	ofs.write((const char*)&maxNumber, sizeof(size_t));
	ofs.write((const char*)&numberBits, sizeof(size_t));
	ofs.write((const char*)data, bucketsCount);
	ofs.close();
}

void MultiSet::deserialize(const char* filename)
{
	if (!filename)
	{
		throw std::invalid_argument("Filename was nullptr.");
	}

	std::ifstream ifs(filename, std::ios::binary);
	if (!ifs.is_open())
	{
		throw std::runtime_error("Stream is already opened.");
	}

	ifs.read((char*)&maxNumber, sizeof(size_t));
	ifs.read((char*)&numberBits, sizeof(size_t));

	unsigned fileSize = getFileSize(ifs);
	bucketsCount = fileSize - (2 * sizeof(size_t));

	delete[] data;
	data = new char[bucketsCount];
	ifs.read((char*)data, bucketsCount);
	ifs.close();
}

MultiSet MultiSet::Complement() const
{
	MultiSet complement = *this;
	for (size_t i = 0; i < bucketsCount; i++)
	{
		complement.data[i] = ~data[i];
	}

	return complement;
}

MultiSet Intersect(const MultiSet& lhs, const MultiSet& rhs)
{
	size_t intersectMaxNumber = (lhs.maxNumber < rhs.maxNumber) ? lhs.maxNumber : rhs.maxNumber;
	size_t intersectNumberBits = (lhs.numberBits < rhs.numberBits) ? lhs.numberBits : rhs.numberBits;

	MultiSet intersection(intersectMaxNumber, intersectNumberBits);

	unsigned intersectionMaxNumCount = powerOfTwo(intersectNumberBits) - 1;

	unsigned lhsNumCount = 0;
	unsigned rhsNumCount = 0;
	for (size_t i = 0; i <= intersectMaxNumber; i++)
	{
		lhsNumCount = lhs.containsCount(i);
		rhsNumCount = rhs.containsCount(i);

		if (lhsNumCount > intersectionMaxNumCount)
		{
			lhsNumCount = intersectionMaxNumCount;
		}
		if (rhsNumCount > intersectionMaxNumCount)
		{
			rhsNumCount = intersectionMaxNumCount;
		}

		if (lhsNumCount < rhsNumCount)
		{
			for (int j = 0; j < lhsNumCount; j++)
			{
				intersection.addNumber(i);
			}
		}
		else
		{
			for (int j = 0; j < rhsNumCount; j++)
			{
				intersection.addNumber(i);
			}
		}
	}

	return intersection;
}

MultiSet Differnce(const MultiSet& lhs, const MultiSet& rhs)
{
	size_t differenceMaxNumber = (lhs.maxNumber > rhs.maxNumber) ? lhs.maxNumber : rhs.maxNumber;
	size_t differenceNumberBits = (lhs.numberBits > rhs.numberBits) ? lhs.numberBits : rhs.numberBits;

	MultiSet difference(differenceMaxNumber, differenceNumberBits);

	unsigned lhsNumCount = 0;
	unsigned rhsNumCount = 0;
	int numsDifference = 0;
	for (size_t i = 0; i <= differenceMaxNumber; i++)
	{
		lhsNumCount = lhs.containsCount(i);
		rhsNumCount = rhs.containsCount(i);

		numsDifference = lhsNumCount - rhsNumCount;
		numsDifference = numsDifference < 0 ? 0 : numsDifference;

		for (int j = 0; j < numsDifference; j++)
		{
			difference.addNumber(i);
		}

	}

	return difference;
}

unsigned powerOfTwo(unsigned n)
{
	if (n > 31)
	{
		return 1;
	}

	return 1 << n;
}

unsigned getFileSize(std::ifstream& ifs)
{
	unsigned currentPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	unsigned size = ifs.tellg();
	ifs.seekg(currentPos);

	return size;
}
