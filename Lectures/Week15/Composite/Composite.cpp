#include <iostream>
#include "Vector.hpp"
#include "PolymorphicPtr.hpp"

class FileSystemEntity
{
public:
    virtual size_t getSize() const = 0;
    virtual ~FileSystemEntity() = default;
};

class File : public FileSystemEntity
{
private:
    size_t size = 0;
public:
    size_t getSize() const override
    {
        return size;
    }
};

class Directory : public FileSystemEntity
{
private:
    Vector<PP<FileSystemEntity>> children;
public:
    size_t getSize() const override
    {
        size_t size = 0;
        for (Vector<PP<FileSystemEntity>>::ConstIterator it = children.cbegin(); it != children.cend(); ++it)
            size += (*it)->getSize();

        return size;
    }
};

int main()
{
}
