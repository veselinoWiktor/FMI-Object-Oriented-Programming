#pragma once
#include <cstdint>

struct Rational {
	int nom;
	int denom;
};

bool isValid(const Rational& rat);
void printRational(const Rational& rat);
unsigned getGcd(unsigned a, unsigned b);
void rationalize(Rational& rat);
Rational& plusEq(Rational& lhs, const Rational& rhs);
Rational plusRationals(const Rational& lhs, const Rational& rhs);
