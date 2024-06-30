#include "SetFactory.h"

Function* SetFactory::createFunction(std::ifstream& ifs, int N)
{
	unsigned* data = new unsigned[N];
	for (size_t i = 0; i < N; i++)
	{
		ifs >> data[i];
	}

	Function* res = new Function(data, N);
	delete[] data;
	return res;
}

Set* SetFactory::createSet(const char* filePath)
{
	std::ifstream ifs(filePath);
	if (!ifs.is_open())
	{
		throw std::exception("cannot open!");
	}
	int N, T;
	ifs >> N >> T;

	char buff[1024];
	Set* res = nullptr;
	Set** sets = nullptr;
	Function* func = nullptr;
	switch (T)
	{
	case 1:
		func = SetFactory::createFunction(ifs, N);
		res = new SetByCriteria<Function>(*func);
		delete func;
		return res;
	case 2:
		sets = new Set * [N];
		for (size_t i = 0; i < N; i++)
		{
			ifs >> buff;
			sets[i] = createSet(buff);
		}
		return new UnionOfSets(sets, N);
	case 3:
		sets = new Set * [N];
		for (size_t i = 0; i < N; i++)
		{
			ifs >> buff;
			sets[i] = createSet(buff);
		}
		return new IntersectionOfSets(sets, N);
	default:
		break;
	}
}
