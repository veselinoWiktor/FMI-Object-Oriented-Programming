#pragma once
#include "Shape.h"

class Circle : public Shape
{
private:
	double radius = 0;

public:
	Circle(int x, int y, double radius);

	double getArea() const override;
	double getPer() const override;
	bool isPointIn(int x, int y) const override;

	void accept(Visitor* visitor) const override;
};

