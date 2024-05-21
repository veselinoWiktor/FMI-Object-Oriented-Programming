#include "StringPool.h"
#include <iostream>
#pragma warning (disable : 4996)

/// <summary>
/// Resizes nodes array
/// </summary>
/// <param name="newCapacity"></param>
void StringPool::resize(size_t newCapacity)
{
	capacity = newCapacity;
	StringNode* temp = new StringNode[capacity];

	for (size_t i = 0; i < count; i++)
	{
		temp[i] = nodes[i];
	}

	delete[] nodes;
	nodes = temp;
}

/// <summary>
/// Binary search for str
/// </summary>
/// <param name="str">String to look by</param>
/// <param name="found">Claims if str is found</param>
/// <returns></returns>
int StringPool::lowerBound(const char* str, bool& found) const
{
	int left = 0;
	int right = count - 1;
	int leftmostIndex = -1;

	while (left <= right)
	{
		int mid = (right - left) / 2 + left;
		int cmp = strcmp(nodes[mid].data, str);

		if (cmp == 0)
		{
			found = true;
			return mid;
		}
		else if (cmp > 0)
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
			leftmostIndex = mid;
		}
	}

	found = false;
	return leftmostIndex;
}

/// <summary>
/// Inserts element
/// </summary>
/// <param name="str"></param>
/// <param name="index"></param>
/// <returns></returns>
const char* StringPool::insert(const char* str, size_t index)
{
	if (index > count)
	{
		throw std::out_of_range("StringPoll::insert() index was out of range");
	}

	if (count == capacity)
	{
		resize(capacity * 2);
	}

	//Shifts the nodes
	for (int i = (count - 1); i >= 0; i--)
	{
		nodes[i + 1] = nodes[i];
	}

	//Allocates new StringNode
	nodes[index].allocateData(str);
	nodes[index].refCount = 1;

	count++;
	return nodes[index].data;
}

/// <summary>
/// Removes element
/// </summary>
/// <param name="index"></param>
void StringPool::removeString(size_t index)
{
	if (index >= count)
	{
		throw std::out_of_range("String::removeString() index was out of range!");
	}

	delete[] nodes[index].data;

	//Shifts element to close the gap
	for (size_t i = index; i < count - 1; i++)
	{
		nodes[i + 1] = nodes[i]; // Shallow copy
	}

	//Set last element to default(fixes shallow copy)
	nodes[count - 1].data = nullptr;
	nodes[count - 1].refCount = 0;

	count--;
}

StringPool::StringPool() : capacity(8), count(0)
{
	nodes = new StringNode[capacity];
}

StringPool::~StringPool()
{
	for (size_t i = 0; i < capacity; i++)
	{
		delete[] nodes[i].data;
	}
	delete[] nodes;
}

const char* StringPool::getString(const char* str)
{
	bool found = false;
	int currentIndex = lowerBound(str, found);

	if (found)
	{
		nodes[currentIndex].refCount++;
		return nodes[currentIndex].data;
	}

	return insert(str, currentIndex + 1);
}

void StringPool::releaseString(const char* str)
{
	bool found = false;
	int idx = lowerBound(str, found);

	if (!found)
	{
		return;
	}

	if (nodes[idx].refCount == 1)
	{
		removeString(idx);
	}
	else
	{
		nodes[idx].refCount--;
	}
}

StringPool::StringNode::StringNode() : data(nullptr), refCount(0)
{
}

void StringPool::StringNode::allocateData(const char* str)
{
	data = new char[strlen(str) + 1];
	strcpy(data, str);
}
