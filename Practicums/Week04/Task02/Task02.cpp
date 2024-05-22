#include <iostream>
#include <fstream>

class Task {
private:
    char* title;
    char* content;
    unsigned points;

public:
    Task() :title(nullptr), content(nullptr), points(0)
    {

    }

    Task(const char* title, const char* content, unsigned points)
    {
        setTitle(title);
        setContent(content);
        setPoint(points);
    }

    ~Task()
    {
        if (!title)
        {
            delete[] title;
        }
        if (!content)
        {
            delete[] content;
        }
    }

    const char* getTitle() const
    {
        return this->title;
    }
    void setTitle(const char* value)
    {
        if (this->title != nullptr)
        {
            delete[] this->title;
        }

        unsigned titleLen = strlen(value);
        this->title = new char[titleLen + 1];
        strcpy(this->title, value);
        this->title[titleLen] = '\0';
    }

    const char* getContent() const
    {
        return this->content;
    }
    void setContent(const char* value)
    {
        if (this->content != nullptr)
        {
            delete[] this->content;
        }

        unsigned contentLen = strlen(value);
        this->content = new char[contentLen + 1];
        strcpy(this->content, value);
        this->content[contentLen] = '\0';
    }

    unsigned getPoints() const
    {
        return this->points;
    }
    void setPoint(unsigned value)
    {
        this->points = value;
    }
};

class Exam {
private:
    Task* tasks;
    size_t tasksSize;
    unsigned minPoints;
    unsigned maxPoints;

    void setTasks(Task* tasks, size_t tasksSize)
    {
        if (tasksSize == 0)
        {
            this->tasks = nullptr;
            return;
        }

        this->tasks = new Task[tasksSize];
        for (size_t i = 0; i < tasksSize; i++)
        {
            this->tasks[i] = tasks[i];
        }
    }

    void setMaxPoints()
    {
        int sum = 0;
        for (size_t i = 0; i < this->tasksSize; i++)
        {
            sum += this->tasks[i].getPoints();
        }

        this->maxPoints = sum;
    }

    void writeToFile(std::ofstream& ofs)
    {
        if (!ofs.is_open())
        {
            return;
        }

        //TODO make save exam to binary file
    }

    void readFromFile(std::ifstream& ifs)
    {
        if (!ifs.is_open())
        {
            return;
        }
    }

public:
    Exam() : tasks(nullptr), tasksSize(0), minPoints(0), maxPoints(0)
    {}

    Exam(Task* tasks, size_t tasksSize, unsigned minPoints)
    {
        setTasks(tasks, tasksSize);
        setMaxPoints();
        changeMinPoints(minPoints);
    }

    ~Exam()
    {
        if (tasks != nullptr)
        {
            delete[] tasks;
        }
    }

    const Task* getTasks() const
    {
        return tasks;
    }

    unsigned getMinPoints() const
    {
        return minPoints;
    }
    void changeMinPoints(unsigned value)
    {
        if (value > this->maxPoints)
        {
            this->minPoints = 0;
        }

        this->minPoints = value;
    }

    unsigned getMax() const
    {
        return this->maxPoints;
    }

    void writeToFile(const char* fileName)
    {
        std::ofstream ofs(fileName, std::ios::binary);
        writeToFile(ofs);
        ofs.close();
    }

    void readFromFile(const char* fileName)
    {
        std::ifstream ifs(fileName, std::ios::binary);
        readFromFile(ifs);
        ifs.close();
    }
};

int main()
{
    std::cout << "Hello World!\n";
}
