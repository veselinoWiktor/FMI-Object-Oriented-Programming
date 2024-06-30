#pragma once
#include "Figure.h"

class Pawn : public Figure
{
public:
	Pawn(bool isWhite);

	bool canBeMoved(size_t currentX, size_t currentY, size_t destX, size_t destY) const override;
	void print() const override;
};


