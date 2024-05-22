#include <iostream>

struct Complex
{
    int realPart;
    int imaginaryPart;
};

void print(const Complex& complexNum)
{
    std::cout << complexNum.realPart << "+" << complexNum.imaginaryPart << "i" << std::endl;
}

Complex sum(const Complex& firstNum, const Complex& secondNum)
{
    int sumRealPart = firstNum.realPart + secondNum.realPart;
    int sumImaginaryPart = firstNum.imaginaryPart + secondNum.imaginaryPart;

    Complex sumNum{ sumRealPart, sumImaginaryPart };
    return sumNum;
}

Complex sub(const Complex& firstNum, const Complex& secondNum)
{
    int subRealPart = firstNum.realPart - secondNum.realPart;
    int subImaginaryPart = firstNum.imaginaryPart - secondNum.imaginaryPart;

    Complex subNum{ subRealPart, subImaginaryPart };
    return subNum;
}

Complex mult(const Complex& firstNum, const Complex& secondNum)
{
    //(a+bi)(c+di) = a*c + a*di + c*bi + -b*d;
    int multRealPart = (firstNum.realPart * secondNum.realPart) - (firstNum.imaginaryPart * secondNum.imaginaryPart);
    int multImaginaryPart = (firstNum.realPart * secondNum.imaginaryPart) + (firstNum.imaginaryPart * secondNum.realPart);

    Complex multNum{ multRealPart, multImaginaryPart };
    return multNum;
}

int main()
{
    Complex firstNum{ 2, 3 };
    Complex secondNum{ 3,4 };
    Complex sumNum = sum(firstNum, secondNum);
    Complex subNum = sub(firstNum, secondNum);
    Complex multNum = mult(firstNum, secondNum);
    print(sumNum);
    print(subNum);
    print(multNum);

}
