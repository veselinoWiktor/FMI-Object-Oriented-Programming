#include "Rectangle.h"

Rectangle::Rectangle(int x1, int y1, int x3, int y3) : Shape(4)
{
	setPoint(0, x1, y1);
	setPoint(1, x1, y3);
	setPoint(2, x3, y3);
	setPoint(3, x3, y1);
}

double Rectangle::getArea() const
{
	return getDistance(points[0], points[1]) * getDistance(points[1], points[2]);
}

bool Rectangle::isPointIn(int x, int y) const
{
	return points[0].x <= x && points[0].y <= y
		&& points[2].x >= x && points[2].y >= y;
}

void Rectangle::accept(Visitor* visitor) const
{
	visitor->visitRectangle(this);
}
