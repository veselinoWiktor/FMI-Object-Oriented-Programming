#include <iostream>

enum class ExitCode {
    Ok,
    NullptrProvided,
    EmptyString,
    InvalidSymbol
};

struct ConversionResult
{
    ExitCode code;
    unsigned int number;
};

bool isDigit(char ch)
{
    return (ch >= '0' && ch <= '9');
}

unsigned charToInt(char ch)
{
    return ch - '0';
}

ConversionResult convertStringToNumber(const char* str)
{
    if (!str)
    {
        return { ExitCode::NullptrProvided, 0 };
    }

    if (!(*str))
    {
        return { ExitCode::EmptyString, 0 };
    }

    unsigned int number = 0;
    while (*str)
    {
        if (!isDigit(*str))
        {
            return { ExitCode::InvalidSymbol, 0 };
        }
        number *= 10;
        number += charToInt(*str);
        str++;
    }

    return { ExitCode::Ok, number };
}

void printExitCode(const ExitCode& code)
{
    switch (code)
    {
    case ExitCode::Ok: std::cout << "ok";
    case ExitCode::NullptrProvided: std::cout << "nullptr provided";
    case ExitCode::InvalidSymbol: std::cout << "invalid string";
    case ExitCode::EmptyString: std::cout << "empty string";
    default:
        break;
    }
}

int main()
{
    const char* myString = "12345e";
    ConversionResult result = convertStringToNumber(myString);

    if (result.code == ExitCode::Ok) {
        std::cout << result.number << std::endl;
    }
    else {
        std::cout << "Error! Exit code: ";
        printExitCode(result.code);
        std::cout << std::endl;
    }

    return 0;
}
