#include <iostream>

namespace Utils
{
    bool isPrime(int n)
    {
        if (n <= 1)
        {
            return false;
        }

        double sqrtN = sqrt(n);
        for (size_t i = 2; i <= sqrtN; i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    int reverse(int n)
    {
        int res = 0;

        while (n != 0)
        {
            int lastDigit = n % 10;
            (res *= 10) += lastDigit;
            n /= 10;
        }

        return res;
    }

    bool isPalindrome(int n)
    {
        return n == reverse(n);
    }

    bool isPowerOfTwo(int n)
    {
        if (n < 0)
        {
            return false;
        }

        return (n & n - 1) == 0;
    }

}


class Interval {
private:
    int a = 0;
    int b = 0;

    unsigned getCountByCriteria(bool (*predicate)(int)) const
    {
        unsigned cnt = 0;

        for (size_t i = a; i <= b; i++)
        {
            if (predicate(i))
            {
                cnt++;
            }
        }

        return cnt;
    }

public:
    Interval() = default;
    Interval(int a, int b)
    {
        if (a > b)
        {
            std::swap(a, b);
        }

        setA(a);
        setB(b);
    }

    void setA(int valA)
    {
        if (valA < b)
        {
            a = valA;
        }
    }
    int getA() const
    {
        return a;
    }

    void setB(int valB)
    {
        if (valB > a)
        {
            b = valB;
        }
    }
    int getB() const
    {
        return b;
    }

    int getLength() const
    {
        return b - a + 1;
    }
    bool isInInterval(int x) const
    {
        return a <= x && x <= b;
    }

    unsigned getCountOfPrimes() const
    {
        return getCountByCriteria(Utils::isPrime);
    }
    unsigned getCountOfPalindromes() const
    {
        return getCountByCriteria(Utils::isPalindrome);
    }
    unsigned getCountOfPowerOfTwo() const
    {
        return getCountByCriteria(Utils::isPowerOfTwo);
    }
};

int main()
{
    Interval i(3, 24);  
    std::cout << i.getCountOfPalindromes() << std::endl;
    std::cout << i.getCountOfPrimes() << std::endl;
    std::cout << i.getCountOfPowerOfTwo() << std::endl;
}
