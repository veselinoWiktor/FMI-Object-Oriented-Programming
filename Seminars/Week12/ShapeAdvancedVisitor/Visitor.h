#pragma once

class Circle;
class Triangle;
class Rectangle;

class Visitor
{
public:
	virtual void visitCircle(const Circle* element) const = 0;
	virtual void visitTriangle(const Triangle* element) const = 0;
	virtual void visitRectangle(const Rectangle* element) const = 0;
};

