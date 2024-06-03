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

	void loadData(std::ifstream& ifs, int16_t N);
	size_t getPairIndex(int32_t x) const;

	void sortPairs();
public:
	FunctionInFile(const String& filePath, int16_t N);
	FunctionInFile(std::ifstream& ifs, int16_t N);
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
void FunctionInFile<CR>::loadData(std::ifstream& ifs, int16_t N)
{
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
	ifs.close();
	sortPairs();
}

template<>
void FunctionInFile<ConstructionRules::OnlyDefinedInGivenNumbers>::loadData(std::ifstream& ifs, int16_t N)
{
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
	sortPairs();
}

template<ConstructionRules CR>
size_t FunctionInFile<CR>::getPairIndex(int32_t x) const //Uses binary search for the pari index
{
	size_t left = 0;
	size_t right = size - 1;

	size_t mid = 0;
	while (left <= right)
	{
		mid = (right - left) / 2 + left;

		size_t currPairX = data[mid].getFirst();
		if (currPairX == x)
		{
			return mid;
		}
		else if (currPairX > x)
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}

	return -1;
}

template<ConstructionRules CR>
void FunctionInFile<CR>::sortPairs() // uses insertion sort to sort the pairs
{
	for (size_t i = 1; i < size; i++)
	{
		Pair<int32_t, int32_t> key = data[i];
		size_t j = i - 1;

		while (j >= 0 && data[j].getFirst() > key.getFirst())
		{
			data[j + 1] = data[j];
			j--;
		}

		data[j + 1] = key;
	}
	
}

template<ConstructionRules CR>
FunctionInFile<CR>::FunctionInFile(const String& filePath, int16_t N)
{
	std::ifstream ifs(filePath.c_str(), std::ios::binary);
	if (!ifs.is_open())
	{
		throw std::logic_error("FunctionInFile(); Cannot open file!");
	}

	loadData(ifs, N);
}

template<ConstructionRules CR>
FunctionInFile<CR>::FunctionInFile(std::ifstream& ifs, int16_t N)
{
	if (!ifs.is_open())
	{
		throw std::logic_error("FunctionInFile(); Cannot open file!");
	}

	loadData(ifs, N);
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
bool FunctionInFile<CR>::contains(int32_t x) const
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
