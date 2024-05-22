#include <iostream>

struct A
{
    int x = 0;
    void print() const {
        std::cout << x;
    }
};

int main()
{
    std::cout << "Hello World!\n";
}
