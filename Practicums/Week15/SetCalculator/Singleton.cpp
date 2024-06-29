#include "Singleton.h"

Singleton::Singleton(char ch) : ch(ch)
{
}

bool Singleton::isElementIn(const Element& element) const
{
	return element.get(ch);
}

SetExpression* Singleton::clone() const
{
	return new Singleton(ch);
}
