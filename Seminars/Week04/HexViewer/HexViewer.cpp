#include <iostream>
#include <fstream>
#include <iomanip>

struct HexViewerFile
{
    unsigned char* content;
    size_t size;
};

size_t getFileSize(std::ifstream& ifs)
{
    size_t currentPos = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    size_t result = ifs.tellg();
    ifs.seekg(currentPos);
    return result;
}

HexViewerFile readFile(const char* filename)
{
    std::ifstream ifs(filename);
    HexViewerFile file;
    if (!ifs.is_open())
    {
        file.content = nullptr;
        file.size = 0;
        return file;
    }

    file.size = getFileSize(ifs);
    file.content = new unsigned char[file.size];
    ifs.read((char*)file.content, file.size);
    ifs.close();
    return file;
}

bool isLetter(char ch)
{
    return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}

void print(const HexViewerFile& file)
{
    for (size_t i = 0; i < file.size; i++)
    {
        std::cout << std::hex << std::setw(2) << (int)file.content[i] << " ";
    }
    std::cout << std::endl;

    for (size_t i = 0; i < file.size; i++)
    {
        if (isLetter(file.content[i]))
        {
            std::cout << std::setw(2) << file.content[i] << " ";
        }
        else
        {
            std::cout << std::setw(2) << ".. ";
        }
    }
    std::cout << std::endl;
}

void modifyByte(HexViewerFile& file, unsigned index, unsigned char value)
{
    if (index >= file.size)
    {
        return;
    }

    file.content[index] = value;
}

void modifyByte(const char* filename, unsigned index, unsigned char value)
{
    if (!filename)
    {
        return;
    }

    std::fstream fs(filename, std::ios::binary | std::ios::out | std::ios::in | std::ios::ate);
    if (!fs.is_open())
    {
        return;
    }

    fs.seekp(index);
    fs.write((const char*)&value, sizeof(char));

    fs.flush();
    fs.close();
}

void saveToFile(const HexViewerFile& file, const char* filename)
{
    if (!filename)
    {
        return;
    }

    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs.is_open())
    {
        return;
    }

    ofs.write((const char*)file.content, file.size);
    ofs.close();
}

int main()
{
    /*HexViewerFile file = readFile("myFile.dat");
    print(file);*/
    modifyByte("myFile.dat", 2, 'r');
    /*print(file);
    saveToFile(file, "resultFile.dat");
    return 0;*/
}