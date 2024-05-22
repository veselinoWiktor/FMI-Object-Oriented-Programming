#include "Rational.h"
#include <iostream>
#include <assert.h>

bool isValid(const Rational& rat)
{
	return rat.denom != 0;
}

void printRational(const Rational& rat)
{
	std::cout << rat.nom << "/" << rat.denom << std::endl;
}

unsigned getGcd(unsigned a, unsigned b)
{
	if (a < b)
	{
		std::swap(a, b);
	}

	while (b != 0)
	{
		int temp = a % b;
		a = b;
		b = temp;
	}

	return a;
}

void rationalize(Rational& rat)
{
	assert(isValid(rat));

	unsigned gcd = getGcd(rat.nom, rat.denom);
	rat.denom /= gcd;
	rat.nom /= gcd;
	if (rat.nom < 0 && rat.denom < 0 || rat.nom > 0 && rat.denom < 0)
	{
		rat.nom *= -1;
		rat.denom *= -1;
	}
}

Rational& plusEq(Rational& lhs, const Rational& rhs)
{
	assert(isValid(lhs) && isValid(rhs));
	lhs.nom *= rhs.denom;
	lhs.nom += rhs.nom * lhs.nom;
	lhs.denom *= rhs.denom;
	rationalize(lhs);
	return lhs;
}

Rational plusRationals(const Rational& lhs, const Rational& rhs)
{
	assert(isValid(lhs) && isValid(rhs));
	Rational lhsCopy = lhs;
	plusEq(lhsCopy, rhs);
	return lhsCopy;
}


