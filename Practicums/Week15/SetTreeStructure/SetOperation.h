#pragma once
#include "Set.h"

class SetOperation : public Set
{
private:
	void copyFrom(const SetOperation& other);
	void moveFrom(SetOperation&& other);
	void free();
	void resize(size_t newCapacity);

protected:
	Set** data;
	size_t size;
	size_t capacity;

	Set** cloneData() const;
	void addSet(Set* set);
public:
	SetOperation();
	SetOperation(const SetOperation& other);
	SetOperation& operator=(const SetOperation& other);
	SetOperation(SetOperation&& other) noexcept;
	SetOperation& operator=(SetOperation&& other) noexcept;
	~SetOperation();
};

