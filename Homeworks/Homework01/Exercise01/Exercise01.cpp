#include <iostream>
#include <fstream>
#include <sstream>

namespace Constants
{
	constexpr unsigned MAX_BUFFER_SIZE = 1024;
	constexpr unsigned MAX_CELLS_IN_ROW = 15;
	constexpr unsigned MAX_CELL_CONTENT_SIZE = 50;
	constexpr unsigned MAX_ROWS_IN_TABLE = 100;
}

namespace Utils
{
	unsigned findStrlen(const char* str)
	{
		if (!str)
		{
			return 0;
		}

		int length = 0;
		while (*str)
		{
			str++;
			length++;
		}

		return length;
	}

	char strCompare(const char* firstStr, const char* secondStr)
	{
		if (!firstStr || !secondStr)
		{
			return (char)1;
		}

		while (*firstStr && *secondStr && *firstStr == *secondStr)
		{
			firstStr++;
			secondStr++;
		}

		return *firstStr - *secondStr;
	}

	void strConcat(char* dest, const char* source, unsigned destinationSpace)
	{
		unsigned destLength = findStrlen(dest);
		unsigned sourceLength = findStrlen(dest);

		if (destLength + sourceLength > destinationSpace)
		{
			return;
		}
		else
		{
			dest += destLength;
			while (*source)
			{
				*dest = *source;
				dest++;
				source++;
			}

			*dest = '\0';
		}
	}
}

enum class TableTag
{
	NoTag = -1,
	Table,
	TableRow,
	TableHeader,
	TableData,
};

struct Cell
{
	char content[Constants::MAX_CELL_CONTENT_SIZE + 1] = "\0";
	TableTag cellType = TableTag::NoTag;
};

struct Row
{
	Cell cells[Constants::MAX_CELLS_IN_ROW];
	size_t cellsCount = 0;
};

struct TagStack
{
	TableTag stack[3]
	{ TableTag::NoTag, TableTag::NoTag, TableTag::NoTag };
	size_t stackSize = 0;
};

class HtmlTable
{
private:
	TagStack tagStack;
	Row rows[Constants::MAX_ROWS_IN_TABLE];
	size_t rowsCount = 0;
	size_t maxCellsCount = 0;
	bool isTagValid = true;
	char* filename = nullptr;

	TableTag parseTag(const char* tag) const
	{
		if (!Utils::strCompare(tag, "table"))
		{
			return TableTag::Table;
		}
		if (!Utils::strCompare(tag, "tr"))
		{
			return TableTag::TableRow;
		}
		if (!Utils::strCompare(tag, "th"))
		{
			return TableTag::TableHeader;
		}
		if (!Utils::strCompare(tag, "td"))
		{
			return TableTag::TableData;
		}
		return TableTag::NoTag;
	}

	void handleClosingTag(const TableTag& tableTag)
	{
		if (tagStack.stack[tagStack.stackSize - 1] == tableTag)
		{
			tagStack.stack[--tagStack.stackSize] = TableTag::NoTag;
		}

		if (tableTag == TableTag::TableRow)
		{
			if (rows[rowsCount].cellsCount > maxCellsCount)
			{
				maxCellsCount = rows[rowsCount].cellsCount;
			}
			rowsCount++;
		}
	}

	void handleOpeningTag(const TableTag& tableTag)
	{
		if (tagStack.stack[tagStack.stackSize - 1] == TableTag::TableData
			|| tagStack.stack[tagStack.stackSize - 1] == TableTag::TableHeader)
		{
			tagStack.stack[tagStack.stackSize - 1] = tableTag;
		}
		else
		{
			tagStack.stack[tagStack.stackSize++] = tableTag;
		}
	}

	void handleTag(const char* tag)
	{
		bool isClosingTag = (*tag == '/') ? true : false;
		if (isClosingTag)
		{
			tag++;
		}

		TableTag tblTg = parseTag(tag);
		if (tblTg != TableTag::NoTag)
		{
			if (!isClosingTag)
			{
				if (!isTagValid)
				{
					tagStack.stack[tagStack.stackSize - 1] = tblTg;
					isTagValid = true;
				}
				else
				{
					handleOpeningTag(tblTg);
				}
			}
			else
			{
				handleClosingTag(tblTg);
			}
		}
		else
		{
			isTagValid = false;
		}
	}

	char handleCharacterEntityReference(const char*& content) const
	{
		content++;
		if (*content != '#')
		{
			content--;
			return '&';
		}

		content++;
		char result = '\0';
		while ('0' <= *content && *content <= '9')
		{
			result *= 10;
			result += (*content - '0');
			content++;
		}

		if (result == '\0')
		{
			content -= 2;
			return '&';
		}
		else
		{
			if ((int)result < 0 || (int)result > 127)
			{
				result = '?';
			}

			content--;
			return result;
		}
	}

	void editContent(Cell& cell, const char* content)
	{
		int currContentIndex = 0;

		unsigned contentLength = 0;
		char currChar = *content;
		while (currChar)
		{
			if (currChar == '&')
			{
				currChar = handleCharacterEntityReference(content);
			}

			(cell).content[currContentIndex++] = currChar;
			content++;
			currChar = *content;
			contentLength++;
		}
		(cell).content[currContentIndex] = '\0';
	}

	void appendContent(Cell& cell, const char* content)
	{
		Utils::strConcat(cell.content, content, Constants::MAX_CELL_CONTENT_SIZE);
	}

	void handleContent(const char* content)
	{
		if (!isTagValid)
		{
			rows[rowsCount].cellsCount--;
		}

		size_t* currRowCellIdx = &(rows[rowsCount].cellsCount);
		Cell* currCell = &(rows[rowsCount].cells[*currRowCellIdx]);

		if (!isTagValid)
		{
			appendContent(*currCell, content);
			isTagValid = true;
		}
		else
		{
			editContent(*currCell, content);

			if (tagStack.stack[tagStack.stackSize - 1] == TableTag::TableHeader)
			{
				(*currCell).cellType = TableTag::TableHeader;
			}
			else if (tagStack.stack[tagStack.stackSize - 1] == TableTag::TableData)
			{
				(*currCell).cellType = TableTag::TableData;
			}
		}
		(*currRowCellIdx)++;
	}

	void readTable()
	{
		std::ifstream ifs(filename);
		if (!ifs.is_open())
		{
			return;
		}

		char buffer[Constants::MAX_BUFFER_SIZE];
		ifs.ignore(Constants::MAX_BUFFER_SIZE, '<');
		while (!ifs.eof())
		{
			ifs.getline(buffer, Constants::MAX_BUFFER_SIZE, '>');
			handleTag(buffer);

			ifs.getline(buffer, Constants::MAX_BUFFER_SIZE, '<');
			if ((tagStack.stack[tagStack.stackSize - 1] == TableTag::TableData
				|| tagStack.stack[tagStack.stackSize - 1] == TableTag::TableHeader)
				&& isTagValid)
			{
				handleContent(buffer);
			}
		}

		ifs.close();
	}

	const int* findCellContentSizes() const
	{
		int* cellContentSizes = new int[maxCellsCount];

		for (size_t i = 0; i < maxCellsCount; i++)
		{
			cellContentSizes[i] = 0;
			int currContentSize = 0;
			for (size_t j = 0; j < rowsCount; j++)
			{
				currContentSize = Utils::findStrlen(rows[j].cells[i].content);
				if (currContentSize > cellContentSizes[i])
				{
					cellContentSizes[i] = currContentSize;
				}
			}
		}

		return cellContentSizes;
	}

	void saveTable() const
	{
		std::ofstream ofs(filename);

		ofs << "<table>\n";
		for (size_t i = 0; i < rowsCount; i++)
		{
			ofs << "\t<tr>\n";
			for (size_t j = 0; j < rows[i].cellsCount; j++)
			{
				if (rows[i].cells[j].cellType == TableTag::TableHeader)
				{
					ofs << "\t\t<th>" << rows[i].cells[j].content << "</th>\n";
				}
				else if (rows[i].cells[j].cellType == TableTag::TableData)
				{
					ofs << "\t\t<td>" << rows[i].cells[j].content << "</td>\n";
				}
			}
			ofs << "\t</tr>\n";
		}
		ofs << "</table>\n";

		ofs.close();
	}

	bool setFilename(const char* value)
	{
		if (!value)
		{
			return false;
		}

		unsigned valueLength = Utils::findStrlen(value);
		filename = new char[valueLength + 1];

		for (int i = 0; i < valueLength; i++)
		{
			filename[i] = value[i];
		}

		filename[valueLength] = '\0';

		return true;
	}

	void UpdateMaxCellsCount()
	{
		if (rowsCount <= 0)
		{
			return;
		}

		int maxCells = 0;
		for (size_t i = 0; i < rowsCount; i++)
		{
			if (rows[i].cellsCount > maxCells)
			{
				maxCells = rows[i].cellsCount;
			}
		}

		maxCellsCount = maxCells;
	}

public:
	HtmlTable() = default;
	HtmlTable(const char* fileName)
	{
		bool state = setFilename(fileName);
		if (state)
		{
			readTable();
		}
	}
	~HtmlTable()
	{
		if (filename != nullptr)
		{
			saveTable();
			delete[] filename;
		}
	}

	void printTable() const
	{
		const int* cellContentSizes = findCellContentSizes();

		for (size_t i = 0; i < rowsCount; i++)
		{
			std::cout << '|';
			for (size_t j = 0; j < maxCellsCount; j++)
			{
				if (rows[i].cells[j].cellType == TableTag::TableHeader)
				{
					std::cout << '*';
				}
				else
				{
					std::cout << ' ';
				}

				std::cout << rows[i].cells[j].content;

				int currContentLength = Utils::findStrlen(rows[i].cells[j].content);
				if (currContentLength < cellContentSizes[j])
				{
					for (size_t k = 0; k < cellContentSizes[j] - currContentLength; k++)
					{
						std::cout << ' ';
					}
				}

				if (rows[i].cells[j].cellType == TableTag::TableHeader)
				{
					std::cout << '*';
				}
				else
				{
					std::cout << ' ';
				}

				std::cout << '|';
			}

			std::cout << std::endl;
		}

		delete[] cellContentSizes;
	}

	void editCell(unsigned rowNumber, unsigned colNumber, const char* newValue)
	{
		rowNumber--;
		colNumber--;
		if (rowNumber < 0 || rowNumber >= rowsCount ||
			colNumber < 0 || colNumber >= maxCellsCount
			|| !newValue)
		{
			return;
		}

		Cell* currCell = &(rows[rowNumber].cells[colNumber]);
		editContent((*currCell), newValue);
	}

	void addRow(unsigned rowNumber, const char* contents)
	{
		if (rowsCount == Constants::MAX_ROWS_IN_TABLE
			|| rowNumber > rowsCount + 1)
		{
			return;
		}

		rowNumber--;
		for (size_t i = rowsCount; i > rowNumber; i--)
		{
			//might need some refactoring;
			rows[i] = rows[i - 1];
		}
		rows[rowNumber] = Row();
		rowsCount++;

		std::stringstream ss(contents);
		char buff[Constants::MAX_BUFFER_SIZE];
		int currCellIdx = 0;
		while (!ss.eof())
		{
			ss.getline(buff, Constants::MAX_BUFFER_SIZE, ' ');

			Cell& currCell = rows[rowNumber].cells[currCellIdx];
			currCell.cellType = TableTag::TableData;

			editContent(currCell, buff);
			currCellIdx++;
		}
		rows[rowNumber].cellsCount = currCellIdx;

		if (currCellIdx > maxCellsCount)
		{
			maxCellsCount = currCellIdx;
		}
	}

	void removeRow(unsigned rowNumber)
	{
		if (rowNumber > rowsCount)
		{
			return;
		}

		rowNumber--;
		int currRowCells = rows[rowNumber].cellsCount;
		for (size_t i = rowNumber; i < rowsCount - 1; i++)
		{
			//might be something that need review
			rows[i] = rows[i + 1];
		}
		rowsCount--;

		if (currRowCells == maxCellsCount)
		{
			UpdateMaxCellsCount();
		}
	}
};

class StartUp
{
public:
	void Run()
	{
		//HtmlTable.txt
		char buff[Constants::MAX_BUFFER_SIZE];
		std::cin.getline(buff, Constants::MAX_BUFFER_SIZE);

		HtmlTable table(buff);

		std::stringstream ss;
		std::cin.getline(buff, Constants::MAX_BUFFER_SIZE);
		while (strcmp(buff, "end"))
		{
			if (!Utils::strCompare(buff, "print"))
			{
				table.printTable();
			}
			else
			{
				ss.clear();
				ss.str(buff);
				ss.getline(buff, Constants::MAX_BUFFER_SIZE, ' ');

				if (!Utils::strCompare(buff, "add"))
				{
					int rowNumber = 0;
					ss >> rowNumber;
					ss.ignore();
					ss.getline(buff, Constants::MAX_BUFFER_SIZE);
					table.addRow(rowNumber, buff);
				}
				else if (!Utils::strCompare(buff, "remove"))
				{
					int rowNumber = 0;
					ss >> rowNumber;
					ss.ignore();
					table.removeRow(rowNumber);
				}
				else if (!Utils::strCompare(buff, "edit"))
				{
					int rowNumber = 0;
					int colNumber = 0;
					ss >> rowNumber >> colNumber;
					ss.ignore();
					ss.getline(buff, Constants::MAX_BUFFER_SIZE);
					table.editCell(rowNumber, colNumber, buff);
				}
			}

			std::cin.getline(buff, Constants::MAX_BUFFER_SIZE);
		}
	}
};

int main()
{
	StartUp startUp;
	startUp.Run();
}