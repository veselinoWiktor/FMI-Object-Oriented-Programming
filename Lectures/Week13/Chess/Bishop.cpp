#include "Bishop.h"

Bishop::Bishop(bool isWhite) : Figure(isWhite, FigureType::BishopFigure)
{
}

bool Bishop::canBeMoved(size_t currentX, size_t currentY, size_t destX, size_t destY) const
{
	return abs(static_cast<int>(currentX) - static_cast<int>(destX)) == abs(static_cast<int>(currentY) - static_cast<int>(currentY));
}

void Bishop::print() const
{
	if (getIsWhite())
		std::cout << 'B';
	else
		std::cout << 'b';
}
