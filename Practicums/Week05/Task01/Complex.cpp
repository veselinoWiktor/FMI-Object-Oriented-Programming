#include "Complex.h"
#include <iostream>

Complex::Complex(int _real, int _imaginary)
{
	setRealPart(_real);
	setImaginaryPart(_imaginary);
}

int Complex::getRealPart() const
{
	return real;
}

void Complex::setRealPart(int value)
{
	real = value;
}

int Complex::getImaginaryPart() const
{
	return imaginary;
}

void Complex::setImaginaryPart(int value)
{
	imaginary = value;
}

bool Complex::isEqual(const Complex& other) const
{
	if (real == other.real && imaginary == other.imaginary)//?
	{
		return true;
	}
	else
	{
		return false;
	}
}

Complex Complex::getConjugated() const
{
	Complex conjugated(real, (-1) * imaginary);
	return conjugated;
}

void Complex::conjugate()
{
	imaginary = (-1) * imaginary;
}

void Complex::print() const
{
	std::cout << real << " + " << imaginary << "i" << std::endl;
}

Complex Complex::add(const Complex& other) const
{
	int realPart = real + other.real;
	int imaginaryPart = imaginary + other.imaginary;

	Complex result(realPart, imaginaryPart);
	return result;
}

Complex Complex::subtract(const Complex& other) const
{
	int realPart = real - other.real;
	int imaginaryPart = imaginary - other.imaginary;

	Complex result(realPart, imaginaryPart);
	return result;
}

Complex Complex::multiply(const Complex& other) const
{
	int realPart = ((real * other.real) - (imaginary * other.imaginary));
	int imaginaryPart = (real * other.imaginary) + (imaginary * other.real);

	Complex result(realPart, imaginaryPart);
	return result;
}
