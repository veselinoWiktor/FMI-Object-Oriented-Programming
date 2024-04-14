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
	return (num * numberBits) / 8;
}

size_t MultiSet::getPosition(unsigned num) const
{
	//(((num + 1) * numberBits) % 8) - 1;
	return (num * numberBits) % 8;
}

size_t MultiSet::bucketsNeeded(size_t num) const
{
	size_t result = ((maxNumber + 1) * numberBits) / 8;
	if ((maxNumber + 1) % 8 != 0)
		result++;

	return result;
}

char MultiSet::getMask(unsigned position) const
{
	return 1 << (7 - position);
}

void MultiSet::setMaxNumber(size_t _maxNumber)
{
	maxNumber = _maxNumber;
}

void MultiSet::setNumberBits(size_t _numberBits)
{
	if (1 <= _numberBits && _numberBits <= 8)
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

void MultiSet::printBucket(unsigned bucketIdx) const
{
	unsigned upperBound = 8;

	if (bucketIdx == bucketsCount - 1)
	{
		unsigned lastNumEndPos = getPosition(maxNumber + 1);
		upperBound = lastNumEndPos == 0 ? upperBound : lastNumEndPos;
		//think of a way to fix it
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

void MultiSet::addNumber(unsigned num)
{
	if (num > maxNumber)
	{
		return; //TODO add exception handling maybe?
	}

	if (containsCount(num) == powerOfTwo(numberBits) - 1)
	{
		return; //TODO add better return message
	}

	int numBucket = getBucket(num);
	int numPosition = getPosition(num);

	int numBitsToRead = numberBits;

	if ((numPosition + numBitsToRead) > 8)
	{
		numPosition = ((numPosition + numBitsToRead) - 8) - 1;
		numBucket++;
	}
	else
	{
		numPosition += (numberBits - 1);
	}

	for (size_t i = 0; i < numBitsToRead; i++)
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
			if (numPosition == 0) {
				numPosition = 7;
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
		return 0; //TODO add exception handling maybe?
	}

	int numBucket = getBucket(num);
	int numPosition = getPosition(num);

	int numBitsToRead = numberBits;
	int numCount = 0;

	for (size_t i = 0; i < numBitsToRead; i++)
	{
		char mask = getMask(numPosition);
		bool bitVal = data[numBucket] & mask;

		numCount |= bitVal;
		numCount <<= 1;

		if (numPosition == 7)
		{
			numPosition = 0;
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
	for (size_t i = 0; i <= maxNumber; i++)
	{
		int currentNumCount = containsCount(i);
		std::cout << i << " is contained:" << currentNumCount << " times." << std::endl;
	}
}

void MultiSet::printMemory() const
{
	for (size_t i = 0; i < bucketsCount; i++)
	{
		printBucket(i);
	}
	std::cout << std::endl;
}

void MultiSet::serialize(const char* filename) const
{
	if (!filename)
	{
		return; //TODO implement error handling
	}

	std::ofstream ofs(filename, std::ios::binary);
	if (!ofs.is_open())
	{
		return; //TODO implement error handling
	}

	//might need revisit
	ofs.write((const char*)data, bucketsCount);
	ofs.close();
}

void MultiSet::deserialize(const char* filename)
{
	if (!filename)
	{
		return; //TODO implement error handling
	}

	std::ifstream ifs(filename, std::ios::binary);
	if (!ifs.is_open())
	{
		return; //TODO implement error handling
	}

	ifs.read((char*)data, bucketsCount);//TODO might need revisit
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

//MultiSet Intersect(const MultiSet& lhs, const MultiSet& rhs)
//{
//	size_t intersectMaxNumber = (lhs.maxNumber < rhs.maxNumber) ? lhs.maxNumber : rhs.maxNumber;
//	//size_t intersectMaxBucketCount = (lhs.maxNumber < rhs.maxNumber) ? lhs.bucketsCount : rhs.bucketsCount;
//	size_t intersectNumberBits = (lhs.numberBits < rhs.numberBits) ? lhs.numberBits : rhs.numberBits;
//
//	MultiSet intersection(intersectMaxNumber, intersectNumberBits);
//}

unsigned powerOfTwo(unsigned n)
{
	if (n > 31)
	{
		return 1;
	}

	return 1 << n;
}
