#pragma once

class ConsolePrinter
{
private:
	bool (*shouldCensore)(char ch);

public:
	ConsolePrinter();
	ConsolePrinter(bool (*pred)(char ch));
	void print(const char* str) const;
};