#include "InteresectVisitor.h"
#include "Intersector.h"
#include <iostream>

void InteresectVisitor::visitCircle(const Circle* element) const
{
	std::cout << "this is circle" << std::endl;
}

void InteresectVisitor::visitTriangle(const Triangle* element) const
{
	std::cout << "this is triangle" << std::endl;
}

void InteresectVisitor::visitRectangle(const Rectangle* element) const
{
	std::cout << "this is rectangle" << std::endl;
}
