#include "ConvertStringToInt.h"

bool isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

int convertCharToNum(char ch)
{
    return ch - '0';
}

ConvertResult convertStringToNumber(const char* str)
{
	if (!str)
	{
		return { ErrorCode::NullptrGiven, 0 };
	}

	if (!*str)
	{
		return { ErrorCode::EmptyString, 0 };
	}

	unsigned num = 0;
	while (*str)
	{
		if (!isDigit(*str))
		{
			return { ErrorCode::WrongCharInString, 0 };
		}

		(num *= 10) += convertCharToNum(*str);
		str++;
	}

	return { ErrorCode::OK, num };
}
