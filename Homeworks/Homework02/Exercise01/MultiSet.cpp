#include "MultiSet.h"

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
	//int dataNum = 0;

	//if ((numPosition + numBitsToRead) > 8)
	//{
	//	dataNum += data[numBucket] & getMask(num, numPosition);

	//	numBitsToRead = (numPosition + numBitsToRead) - 8;
	//	dataNum <<= numBitsToRead;
	//	numPosition = 0;
	//	numBucket++;
	//	inTwoBuckets = true;
	//}

	//dataNum += data[numBucket] & getMask(num, numPosition, numBitsToRead);

	////check for dataNum == 2^k - 1;
	//if (dataNum == (powerOfTwo(numberBits) - 1))
	//{
	//	return; //TODO exception handling
	//}
	//else
	//{
	//	dataNum++;
	//}

	//if (inTwoBuckets)
	//{
	//	
	//}

	if ((numPosition + numBitsToRead) > 8)
	{
		//go to the end of num
		numPosition = ((numPosition + numBitsToRead) - 8) - 1;
		numBucket++;
	}
	else
	{
		numPosition += (numberBits - 1);
	}

	for (size_t i = 0; i < numBitsToRead; i++)
	{
		//check num at position in bucket
		char mask = getMask(numPosition);
		bool bitVal = data[numBucket] & mask;

		//if 0 make it 1 and break cycle because we incremented it by one;
		if (!bitVal)
		{
			data[numBucket] |= mask;
			break;
		}
		else //if 1 go to next iteration and make it zero
		{
			data[numBucket] &= ~mask;
			if (numPosition == 0) {
				//if position goes to zero and still have iterations, go to previous bucket and increment by one
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

unsigned MultiSet::containsCount(unsigned num)
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

unsigned powerOfTwo(unsigned n)
{
	if (n > 31)
	{
		return 1;
	}

	return 1 << n;
}
