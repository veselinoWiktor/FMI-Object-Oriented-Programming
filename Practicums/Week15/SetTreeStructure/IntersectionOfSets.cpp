#include "IntersectionOfSets.h"

IntersectionOfSets::IntersectionOfSets(Set** sets, size_t setsSize)
{
	for (size_t i = 0; i < setsSize; i++)
	{
		addSet(sets[i]);
	}
}

bool IntersectionOfSets::accepts(unsigned int n) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i]->accepts(n))
		{
			return true;
		}
	}
	return false;
}

Set* IntersectionOfSets::clone() const
{
	return new IntersectionOfSets(cloneData(), size);
}
