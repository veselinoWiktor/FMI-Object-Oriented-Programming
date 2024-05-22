#include <iostream>
#include <fstream>

constexpr size_t MAX_WORD_SIZE = 32;

struct KeyValue
{
	char key[MAX_WORD_SIZE];
	char value[MAX_WORD_SIZE];
};

bool myStrcmp(const char* firstStr, const char* secondStr)
{
	if (!firstStr || !secondStr)
	{
		return false;
	}

	while ((*firstStr) && (*secondStr) && (*firstStr == *secondStr))
	{
		firstStr++;
		secondStr++;
	}

	return (!(*firstStr - *secondStr));
}

void swapKyWthVlInSprtFls(std::ifstream& ifs, const KeyValue& kv)
{
	if (!ifs.is_open())
	{
		return;
	}

	std::ofstream ofs("result.txt");
	if (!ofs.is_open())
	{
		return;
	}

	char currentWord[MAX_WORD_SIZE];

	while (!ifs.eof())
	{
		ifs >> currentWord;
		char delmiter = '\0';
		
		if (!ifs.eof())
		{
			delmiter = ifs.get();
		}

		if (myStrcmp(kv.key, currentWord))
		{
			ofs << kv.value << delmiter;
		}
		else
		{
			ofs << currentWord << delmiter;
		}
	}

	ofs.close();
}

void swapKyWthVlInSmFls(std::ifstream& ifs, const KeyValue kv[], size_t kvSize)
{
	if (!ifs.is_open())
	{
		return;
	}

	std::ofstream ofs("result.txt");
	if (!ofs.is_open())
	{
		return;
	}

	char currentWord[MAX_WORD_SIZE];

	while (!ifs.eof())
	{
		ifs >> currentWord;
		char delmiter = '\0';

		if (!ifs.eof())
		{
			delmiter = ifs.get();
		}

		int matchIndex = -1;
		for (size_t i = 0; i < kvSize; i++)
		{
			KeyValue currentKV = kv[i];
			if (myStrcmp(currentKV.key, currentWord))
			{
				matchIndex = i;
			}
		}

		if (matchIndex == -1)
		{
			ofs << currentWord << delmiter;
			std::cout << "a";
		}
		else if (0 <= matchIndex && matchIndex <= kvSize - 1)
		{
			ofs << kv[matchIndex].value << delmiter;
			std::cout << "b";
		}
	}

	ofs.close();
}

int main()
{
	std::ifstream ifs("input.txt");
	KeyValue kv[] = { { "viktor", "veselinov" },{"e", "ee"}};
	swapKyWthVlInSmFls(ifs, kv, 2);
	ifs.close();
}
