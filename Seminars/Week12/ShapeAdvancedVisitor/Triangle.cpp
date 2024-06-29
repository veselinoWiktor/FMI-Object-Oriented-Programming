#include "Triangle.h"

Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3) : Shape(3)
{
	setPoint(0, x1, y1);
	setPoint(1, x2, y2);
	setPoint(2, x3, y3);
}

double Triangle::getArea() const
{
	const Shape::Point& p1 = getPoint(0);
	const Shape::Point& p2 = getPoint(1);
	const Shape::Point& p3 = getPoint(2);

	return abs(p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p2.y * p3.x - p3.y * p1.x - p1.y * p2.x) / 2.00; //Formula with the determinant
}

bool Triangle::isPointIn(int x, int y) const
{
	Shape::Point p(x, y);
	Triangle t1(getPoint(0).x, getPoint(0).y, getPoint(1).x, getPoint(1).y, p.x, p.y);
	Triangle t2(getPoint(2).x, getPoint(2).y, getPoint(1).x, getPoint(1).y, p.x, p.y);
	Triangle t3(getPoint(2).x, getPoint(2).y, getPoint(0).x, getPoint(0).y, p.x, p.y);

	return abs(t1.getArea() + t2.getArea() + t3.getArea() - getArea()) <= std::numeric_limits<double>::epsilon();
}

void Triangle::accept(Visitor* visitor) const
{
	visitor->visitTriangle(this);
}