#include "SetFactory.h"

Set* SetFactory::createSetByCriteria(std::ifstream& ifs, int N)
{
	unsigned* data = new unsigned[N];
	for (size_t i = 0; i < N; i++)
	{
		ifs >> data[i];
	}

	Function func(data, N);
	return new SetByCriteria<Function>(func);
}

Set* SetFactory::createUnionOfSets(std::ifstream& ifs, int N)
{
	Set** sets = new Set * [N];
	char buff[1024];
	for (size_t i = 0; i < N; i++)
	{
		ifs >> buff;
		sets[i] = createSet(buff);
	}
	return new UnionOfSets(sets, N);
}

Set* SetFactory::createIntersectionOfSets(std::ifstream& ifs, int N)
{
	Set** sets = new Set * [N];
	char buff[1024];
	for (size_t i = 0; i < N; i++)
	{
		ifs >> buff;
		sets[i] = createSet(buff);
	}
	return new IntersectionOfSets(sets, N);
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

	switch (T)
	{
	case 1:
		return createSetByCriteria(ifs, N);
	case 2:
		return createUnionOfSets(ifs, N);
	case 3:
		return createIntersectionOfSets(ifs, N);
	default:
		break;
	}
}
