#include "Pawn.h"

Pawn::Pawn(bool isWhite) : Figure(isWhite, PawnFigure)
{
}

bool Pawn::canBeMoved(size_t currentX, size_t currentY, size_t destX, size_t destY) const
{
	if (getIsWhite())
		return currentY - 1 == destY 
			&& abs(static_cast<int>(currentX) - static_cast<int>(destX)) <= 1;
	else
		return currentY + 1 == destY 
			&& abs(static_cast<int>(currentX) - static_cast<int>(destX)) <= 1;
}

void Pawn::print() const
{
	if (getIsWhite())
		std::cout << 'P';
	else
		std::cout << 'p';
}
