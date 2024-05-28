#pragma once

#include <iostream>

#include "Pair.hpp"
#include "String.h"

enum class ConstructionRules
{
	OnlyDefinedInGivenNumbers = 0, // T = 0
	NotDefinedInGivenNumbers = 1, // T = 1
	DefinedForEachNumber = 2, // T = 2
};

//TODO implement binary save and search of the Pairs;
template<ConstructionRules CR>
class FunctionInFile
{
private:
	Pair<int32_t,int32_t>* data;
	size_t size;

	void copyFrom(const FunctionInFile<CR>& other);
	void moveFrom(FunctionInFile<CR>&& other);
	void free();

	void loadData(const String& filePath, int16_t N);
	size_t getPairIndex(int32_t x) const;
public:
	FunctionInFile(const String& filePath, int16_t N); // Might want to implement FilePath class
	FunctionInFile(const FunctionInFile<CR>& other);
	FunctionInFile(FunctionInFile<CR>&& other) noexcept;
	FunctionInFile<CR>& operator=(const FunctionInFile<CR>& other);
	FunctionInFile<CR>& operator=(FunctionInFile<CR>&& other);
	~FunctionInFile();

	bool contains(int32_t x) const;
	Pair<bool, int32_t> operator()(int32_t x) const;
};

template<ConstructionRules CR>
void FunctionInFile<CR>::copyFrom(const FunctionInFile<CR>& other)
{
	size = other.size;
	data = new Pair<int,int>[size];
	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}

template<ConstructionRules CR>
void FunctionInFile<CR>::moveFrom(FunctionInFile<CR>&& other)
{
	size = other.size;

	data = other.data;
	other.data = nullptr;
}

template<ConstructionRules CR>
void FunctionInFile<CR>::free()
{
	delete[] data;
}

template<ConstructionRules CR>
void FunctionInFile<CR>::loadData(const String& filePath, int16_t N)
{
	std::ifstream ifs(filePath.c_str(), std::ios::binary);
	if (!ifs.is_open())
	{
		throw std::logic_error("FunctionInFile::loadData(); Cannot open file!");
	}

	data = new Pair<int32_t, int32_t>[N];
	int32_t* row = new int32_t[N];
	ifs.read((char*)row, sizeof(int32_t) * N);
	for (size_t i = 0; i < N; i++)
	{
		data[i].setFirst(row[i]);
	}

	for (size_t i = 0; i < N; i++)
	{
		data[i].setSecond(0);
	}

	size = N;
	delete[] row;
}

template<>
void FunctionInFile<ConstructionRules::OnlyDefinedInGivenNumbers>::loadData(const String& filePath, int16_t N)
{
	std::ifstream ifs(filePath.c_str(), std::ios::binary);
	if (!ifs.is_open())
	{
		throw std::logic_error("FunctionInFile::loadData(); Cannot open file!");
	}

	data = new Pair<int32_t, int32_t>[N];
	int32_t* row = new int32_t[N];
	ifs.read((char*)row, sizeof(int32_t) * N);
	for (size_t i = 0; i < N; i++)
	{
		data[i].setFirst(row[i]);
	}

	ifs.read((char*)row, sizeof(int32_t) * N);
	for (size_t i = 0; i < N; i++)
	{
		data[i].setSecond(row[i]);
	}

	delete[] row;
	size = N;
	ifs.close();
}

template<ConstructionRules CR>
size_t FunctionInFile<CR>::getPairIndex(int32_t x) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i].getFirst() == x)
		{
			return i;
		}
	}
	return -1;
}

template<ConstructionRules CR>
FunctionInFile<CR>::FunctionInFile(const String& filePath, int16_t N)
{
	loadData(filePath, N);
}

template<ConstructionRules CR>
FunctionInFile<CR>::FunctionInFile(const FunctionInFile<CR>& other)
{
	copyFrom(other);
}

template<ConstructionRules CR>
FunctionInFile<CR>::FunctionInFile(FunctionInFile<CR>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<ConstructionRules CR>
FunctionInFile<CR>& FunctionInFile<CR>::operator=(const FunctionInFile<CR>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<ConstructionRules CR>
FunctionInFile<CR>& FunctionInFile<CR>::operator=(FunctionInFile<CR>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<ConstructionRules CR>
FunctionInFile<CR>::~FunctionInFile()
{
	free();
}

template<ConstructionRules CR>
bool FunctionInFile<CR>
::contains(int32_t x) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i].getFirst() == x)
		{
			return true;
		}
	}
	return false;
}

template<>
Pair<bool, int32_t> FunctionInFile<ConstructionRules::OnlyDefinedInGivenNumbers>::operator()(int32_t x) const
{
	size_t xPairIdx = getPairIndex(x);
	if (xPairIdx == -1)
	{
		return Pair<bool, int>(false, 0);
	}
	else
	{
		return Pair<bool, int>(true, data[xPairIdx].getSecond());
	}
}

template<>
Pair<bool, int32_t> FunctionInFile<ConstructionRules::NotDefinedInGivenNumbers>::operator()(int32_t x) const
{
	if (contains(x))
	{
		return Pair<bool, int>(false, 0);
	}
	else
	{
		return Pair<bool, int>(true, x);
	}
}

template<>
Pair<bool, int32_t> FunctionInFile<ConstructionRules::DefinedForEachNumber>::operator()(int32_t x) const
{
	if (contains(x))
	{
		return Pair<bool, int>(true, 1);
	}
	else
	{
		return Pair<bool, int>(true, 0);
	}
}
