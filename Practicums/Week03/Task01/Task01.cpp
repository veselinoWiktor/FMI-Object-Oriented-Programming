#include <iostream>
#include <fstream>
#include <sstream>	

namespace Constants {
	constexpr int MATRIX_MAX_SIZE = 5;
	constexpr int MAX_BUFF_SIZE = 1024;

	const char ROW_DELMITER = '|';
	const char COL_DELMITER = ',';
}

typedef int Cell;

struct Row
{
	Cell cells[Constants::MATRIX_MAX_SIZE];
};

struct Matrix
{
	Row rows[Constants::MATRIX_MAX_SIZE];
	size_t rowSize = 0;
	size_t colSize = 0;
};

size_t findMatrixRowSize(const char* matrixString)
{
	if (!matrixString)
	{
		return 0;
	}

	int rowCount = 1;
	while (*matrixString)
	{
		if (*matrixString == '|')
		{
			rowCount++;
		}
	}
}

int parseCharToInt(char ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return ch - '0';
	}
}

int parseStrToInt(const char* str)
{
	if (!str)
	{
		return 0;
	}

	int result = 0;
	while (*str)
	{
		result *= 10;
		result += parseCharToInt(*str);
		str++;
	}

	return result;
}

Row parseRow(const char* matrixRow, size_t matrixCols)
{
	std::stringstream ss(matrixRow);

	Row row;
	char cellBuff[Constants::MAX_BUFF_SIZE];
	for (int i = 0; i < matrixCols; i++)
	{
		if (matrixCols - 1 == i)
		{
			ss.getline(cellBuff, Constants::MAX_BUFF_SIZE, '|');
		}
		else
		{
			ss.getline(cellBuff, Constants::MAX_BUFF_SIZE, ',');
		}

		row.cells[i] = parseStrToInt(cellBuff);
	}

	return row;
}

void findMatrixDimensions(std::ifstream& ifs, Matrix& matrix)
{
	char currentSymbol = '\0';
	ifs.get(currentSymbol);

	while (!ifs.eof() && currentSymbol != '|')
	{
		if (currentSymbol == ',')
		{
			matrix.colSize++;
		}

		ifs.get(currentSymbol);
	}

	matrix.colSize++;

	while (!ifs.eof())
	{
		if (currentSymbol == '|')
		{
			matrix.rowSize++;
		}
		ifs.get(currentSymbol);
	}

	matrix.rowSize++;

	ifs.clear();
	ifs.seekg(0, std::ios::beg);
}

Matrix readMatrix(const char* matrixFileName)
{
	std::ifstream ifs(matrixFileName);
	if (!ifs.is_open())
	{
		return {};
	}

	Matrix matrix;
	findMatrixDimensions(ifs, matrix);
	char matrixRow[Constants::MAX_BUFF_SIZE];
	for (int i = 0; i < matrix.rowSize; i++)
	{
		ifs.getline(matrixRow, Constants::MAX_BUFF_SIZE, '|');
		matrix.rows[i] = parseRow(matrixRow, matrix.colSize);
	}

	return matrix;
}

int findCellValue(const Matrix& first, const Matrix& second, int firstRow, int secondCol)
{
	int result = 0;
	for (size_t i = 0; i < first.colSize; i++)
	{
		result += first.rows[firstRow].cells[i] * second.rows[i].cells[secondCol];
	}

	return result;
}

Matrix findMatrixProduct(const Matrix& fstMatrix, const Matrix& sndMatrix)
{
	if (fstMatrix.colSize != sndMatrix.rowSize)
	{
		return {};
	}

	Matrix product{};
	product.rowSize = fstMatrix.rowSize;
	product.colSize = sndMatrix.colSize;
	for (size_t i = 0; i < product.rowSize; i++)
	{
		for (size_t j = 0; j < product.colSize; j++)
		{
			product.rows[i].cells[j] = findCellValue(fstMatrix, sndMatrix, i, j);
		}
	}

	return product;
}

void printRow(std::ofstream& ofs, const Row& row, size_t matrixCols)
{
	for (size_t i = 0; i < matrixCols - 1; i++)
	{
		ofs << row.cells[i] << ',';
	}
	ofs << row.cells[matrixCols - 1];
}

void printMatrix(const Matrix& matrix)
{
	std::ofstream ofs("result.txt");
	if (!ofs.is_open())
	{
		return;
	}

	for (size_t i = 0; i < matrix.rowSize - 1; i++)
	{
		printRow(ofs, matrix.rows[i], matrix.colSize);
		ofs << '|';
	}
	printRow(ofs, matrix.rows[matrix.rowSize - 1], matrix.colSize);

	ofs.close();
}

int main()
{
	Matrix firstMatrix = readMatrix("fst.txt");
	Matrix secondMatrix = readMatrix("snd.txt");

	Matrix product = findMatrixProduct(firstMatrix, secondMatrix);

	printMatrix(product);
}
