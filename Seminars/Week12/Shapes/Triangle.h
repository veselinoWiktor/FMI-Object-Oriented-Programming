#pragma once
#include "Shape.h"

class Triangle : public Shape
{
public:
	Triangle(int x1, int y1, int x2, int y2, int x3, int y3);

	double getArea() const override;
	bool isPointIn(int x, int y) const override;

	bool intersect(const Shape*) const override;
	bool intersectWithCircle(const Circle*) const override;
	bool intersectWithTriangle(const Triangle*) const override;
	bool intersectWithRectangle(const Rectangle*) const override;
};

