#include "Figure.h"

Figure::Figure(bool isWhite, FigureType type) : isWhite(isWhite), figureType(type)
{
}

bool Figure::getIsWhite() const
{
	return isWhite;
}

FigureType Figure::getType() const
{
	return figureType;
}
