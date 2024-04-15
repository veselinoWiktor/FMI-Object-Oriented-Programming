#pragma once
#include<fstream>

namespace MultiSetConstants {
	constexpr const int FIRST_BIT_INDEX = 0;
	constexpr const int LAST_BIT_INDEX = 7;

	constexpr const int BITS_IN_BYTE = 8;

	constexpr const int MIN_BITS_FOR_NUMBER = 0;
	constexpr const int MAX_BITS_FOR_NUMBER = 8;
}

class MultiSet
{
private:
	size_t numberBits = 0;

	char* data = nullptr;
	size_t maxNumber = 0;
	size_t bucketsCount = 0;

	void copyFrom(const MultiSet& other);
	void free();

	size_t getBucket(unsigned num) const;
	size_t getPosition(unsigned num) const;
	size_t bucketsNeeded(size_t num) const;
	char getMask(unsigned position) const;

	void setMaxNumber(size_t _maxNumber);
	void setNumberBits(size_t _numberBits);
	void initData();

	void printBucketMemory(unsigned bucketIdx) const;
public:
	MultiSet() = default;
	MultiSet(size_t n, size_t k);
	MultiSet(const MultiSet& other);
	MultiSet& operator=(const MultiSet& other);
	~MultiSet();

	void addNumber(unsigned num);
	unsigned containsCount(unsigned num) const;
	void print() const;
	void printMemory() const;
	void serialize(const char* filename) const;
	void deserialize(const char* filename);

	//friend MultiSet Union(const MultiSet& lhs, const MultiSet& rhs);
	friend MultiSet Intersect(const MultiSet& lhs, const MultiSet& rhs);
	friend MultiSet Differnce(const MultiSet& lhs, const MultiSet& rhs);
	MultiSet Complement() const;
};

unsigned powerOfTwo(unsigned n);
unsigned getFileSize(std::ifstream& ifs);
