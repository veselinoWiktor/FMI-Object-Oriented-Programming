#include "King.h"

King::King(bool isWhite) : Figure(isWhite, FigureType::KingFigure)
{
}

bool King::canBeMoved(size_t currentX, size_t currentY, size_t destX, size_t destY) const
{
	return abs(static_cast<int>(currentX) - static_cast<int>(destX)) <= 1
		&& abs(static_cast<int>(currentY) - static_cast<int>(destY)) <= 1;
}

void King::print() const
{
	if (getIsWhite())
		std::cout << '%';
	else
		std::cout << '$';
}
