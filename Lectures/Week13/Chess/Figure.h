#pragma once
#include <iostream>
#include "ConfigEnum.h"

class Figure
{
private:
	bool isWhite;
	FigureType figureType;
public:
	Figure(bool isWhite, FigureType type);
	virtual ~Figure() = default;

	virtual bool canBeMoved(size_t currentX, size_t currentY, size_t destX, size_t destY) const = 0;
	virtual void print() const = 0;

	bool getIsWhite() const;
	FigureType getType() const;
};

