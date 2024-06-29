#include "Intersector.h"

bool Intersector::intersect(const Shape* shape1, const Shape* shape2)
{
	Visitor* iv = new InteresectVisitor;
	shape1->accept(iv);
}
