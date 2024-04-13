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

size_t MultiSet::bucketsNeeded(size_t n) const
{
    size_t result = ((maxNumber + 1) * numberBits) / 8;
    if ((maxNumber + 1) % 8 != 0)
        result++;

    return result;
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
