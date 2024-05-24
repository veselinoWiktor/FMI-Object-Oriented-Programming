#pragma once
#include "Collection.h"
#include "PureNumberCollection.h"

enum CollectionType
{
	NORMAL_COLLECTION,
	SORTED_COLLECTION
};

class Set : public Collection
{
	PureNumberCollection* collection;

public:
	Set(CollectionType);

	Set(const Set&) = delete;
	Set& operator=(const Set&) = delete;

	void add(int elem) override;
	void remove(int elem) override;
	unsigned count(int elem) const override;
	bool contains(int elem) const override;

	~Set();
};

