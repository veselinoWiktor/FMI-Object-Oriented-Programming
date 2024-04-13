#pragma once

class MultiSet
{
private:
	size_t numberBits = 0;

	char* data = nullptr;
	size_t maxNumber = 0;
	size_t bucketsCount = 0;

	void copyFrom(const MultiSet& other);
	void free();

	size_t getBucket(unsigned n) const;
	size_t getPosition(unsigned n) const;
	size_t bucketsNeeded(size_t n) const;

	void setMaxNumber(size_t _maxNumber);
	void setNumberBits(size_t _numberBits);
	void initData();
public:
	MultiSet() = default;
	MultiSet(size_t n, size_t k);
	MultiSet(const MultiSet& other);
	MultiSet& operator=(const MultiSet& other);
	~MultiSet();

	void addNumber();
	unsigned containsCount(unsigned number);
	void print();
	void serailize();
	void deserialize();
};