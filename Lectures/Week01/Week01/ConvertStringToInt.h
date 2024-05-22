#pragma once
#include <iostream>

bool isDigit(char ch);
int convertCharToNum(char ch);

enum class ErrorCode
{
	OK,
	NullptrGiven,
	WrongCharInString,
	EmptyString
};

struct ConverResult
{
	ErrorCode errCode;
	unsigned result;
};

ConverResult convertStringToNumber(const char* str);