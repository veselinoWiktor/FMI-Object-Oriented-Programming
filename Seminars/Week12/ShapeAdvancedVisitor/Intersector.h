#pragma once
#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "InteresectVisitor.h"

class Intersector
{
public:
	static bool intersect(const Shape* shape1, const Shape* shape2);
	static bool intersect(const Circle* shape1, const Circle* shape2);
	static bool intersect(const Circle* shape1, const Triangle* shape2);
	static bool intersect(const Circle* shape1, const Rectangle* shape2);
	static bool intersect(const Triangle* shape1, const Triangle* shape2);
	static bool intersect(const Triangle* shape1, const Rectangle* shape2);
	static bool intersect(const Rectangle* shape1, const Rectangle* shape2);
};

