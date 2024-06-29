#pragma once
#include "Visitor.h"

class InteresectVisitor : public Visitor
{
	void visitCircle(const Circle* element) const override;
	void visitTriangle(const Triangle* element) const override;
	void visitRectangle(const Rectangle* element) const override;
};

