#include <iostream>
#include <assert.h>

struct Rational
{
    int nominator;
    int denominator;
};

bool isValid(const Rational& rational)
{
    return rational.denominator != 0;
}

void printRational(const Rational& rational)
{
    assert(isValid(rational));

    std::cout << rational.nominator << "/" << rational.denominator;
}

int gcd(int a, int b)
{
    if (a < b)
    {
        std::swap(a, b);
    }


    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

void rationalize(Rational& rational)
{
    assert(isValid(rational));

    int gcdRat = gcd(rational.nominator, rational.denominator);
    rational.nominator /= gcdRat;
    rational.denominator /= gcdRat;
}

Rational sumRationals(const Rational& lhs, const Rational& rhs)
{
    assert(isValid(lhs) && isValid(rhs));

    int summedNominator = (lhs.nominator * rhs.denominator) + (lhs.denominator * rhs.nominator);
    int summedDenominator = (lhs.denominator * rhs.denominator);

    Rational sumRational{ summedNominator, summedDenominator };
    rationalize(sumRational);
    return sumRational;
}

int main()
{
    Rational a{ 1,6 };
    Rational b{ 1,3 };

    Rational sum = sumRationals(a, b);
    printRational(sum);
}
