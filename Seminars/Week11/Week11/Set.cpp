#include "Set.h"
#include "NormalCollection.h"
#include "SortedCollection.h"

Set::Set(CollectionType type)
{
	if (type == NORMAL_COLLECTION)
	{
		collection = new NormalCollection();
	}
	else if (type == SORTED_COLLECTION)
	{
		collection = new SortedCollection();
	}
	else
	{
		throw std::logic_error("Set type was wrong!");
	}
}

void Set::add(int elem)
{
	if (!contains(elem))
	{
		(*collection).add(elem);
	}
}

void Set::remove(int elem)
{
	collection->remove(elem);
}

unsigned Set::count(int elem) const
{
	return collection->count(elem);
}

bool Set::contains(int elem) const
{
	return collection->contains(elem);
}

Set::~Set()
{
	delete collection;
}
