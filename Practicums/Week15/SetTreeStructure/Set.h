#pragma once

class Set
{
public:
	Set() = default;
	virtual bool accepts(unsigned int n) const = 0;
	virtual Set* clone() const = 0;
	virtual ~Set() = default;
};