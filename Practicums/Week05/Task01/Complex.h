#pragma once

class Complex
{
private:
	int real = 0;
	int imaginary = 0;
public:
	Complex() = default;
	Complex(int _real, int _imaginary);

	int getRealPart() const;
	void setRealPart(int value);
	int getImaginaryPart() const;
	void setImaginaryPart(int value);

	bool isEqual(const Complex& other) const;
	Complex getConjugated() const;
	void conjugate();
	void print() const;

	Complex add(const Complex& other) const;
	Complex subtract(const Complex& other) const;
	Complex multiply(const Complex& other) const;
};