#include "UnionOfSets.h"

UnionOfSets::UnionOfSets(Set** sets, size_t setsSize)
{
	for (size_t i = 0; i < setsSize; i++)
	{
		addSet(sets[i]);
	}
}

bool UnionOfSets::accepts(unsigned int n) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (!data[i]->accepts(n))
		{
			return false;
		}
	}
	return true;
}

Set* UnionOfSets::clone() const
{
	return new UnionOfSets(cloneData(), size);
}
