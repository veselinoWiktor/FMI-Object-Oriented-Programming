#include "ArrFileReader.h"
#include "ArrFileWriter.h"
#include "BinaryFileReader.h"
#include "BinaryFileWriter.h"
#include "CSVFileReader.h"
#include "CSVFileWriter.h"
#include "FilePath.h"

FileReader* getFileReader(const String& filename) {
	FilePath filepath(filename);
	if (filepath.getExtension() == ".csv") {
		return new CSVFileReader(filename);
	}
	if (filepath.getExtension() == ".arr") {
		return new ArrFileReader(filename);
	}
	if (filepath.getExtension() == ".dat") {
		return new BinaryFileReader(filename);
	}
	throw std::exception("Invalid file extension!");
}

FileWriter* getFileWriter(const String& filename) {
	FilePath filepath(filename);
	if (filepath.getExtension() == ".csv") {
		return new CSVFileWriter(filename);
	}
	if (filepath.getExtension() == ".arr") {
		return new ArrFileWriter(filename);
	}
	if (filepath.getExtension() == ".dat") {
		return new BinaryFileWriter(filename);
	}
	throw std::exception("Invalid file extension!");
}

void convert(const String& sourceFile, const String& destFile) {
	FileReader* fileReader = getFileReader(sourceFile);
	size_t size = 0;
	int* arr = fileReader->read(size);

	FileWriter* fileWriter = getFileWriter(destFile);
	fileWriter->write(arr, size);

	delete[] arr;
	delete fileReader;
	delete fileWriter;
}