#include <iostream>
#include "ConsolePrinter.h"

ConsolePrinter::ConsolePrinter()
    : shouldCensore([](char ch) {return false; })
{
    
}

ConsolePrinter::ConsolePrinter(bool(*pred)(char ch))
    : shouldCensore(pred)
{
}

void ConsolePrinter::print(const char* str) const
{
    while (*str)
    {
        if (shouldCensore(*str))
        {
            std::cout << '*';
        }
        else
        {
            std::cout << *str;
        }
        str++;
    }
    std::cout << std::endl;
}
