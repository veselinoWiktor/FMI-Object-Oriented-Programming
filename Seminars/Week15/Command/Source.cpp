#include <iostream>
#include "SortCommand.h"
#include "SwapCommand.h"

void printArray(const IntVector& v)
{
	for (size_t i = 0; i < v.getSize(); i++)
		std::cout << v[i] << " ";
	std::cout << std::endl;
}

class CommandExecutor
{
private:
	Vector<VectorCommand*> waiting;
	Vector<VectorCommand*> executed;
public:
	CommandExecutor() = default;
	CommandExecutor(const CommandExecutor&) = delete;
	CommandExecutor& operator=(const CommandExecutor&) = delete;

	void addCommand(VectorCommand* command)
	{
		if (!command)
			throw std::invalid_argument("Invalid command!");
		waiting.pushBack(command);
	}

	void execute()
	{
		if (waiting.empty())
		{
			throw std::runtime_error("No more commands!");
		}
		waiting[0]->execute();
		executed.pushBack(waiting.popAt(0));
	}

	void executeAll()
	{
		while (!waiting.empty())
		{
			execute();
		}
	}

	void undo()
	{
		if (executed.empty())
		{
			throw std::runtime_error("No command to undo!");
		}
		executed[executed.getSize() - 1]->undo();
		delete executed.popBack();
	}

	~CommandExecutor()
	{
		for (size_t i = 0; i < waiting.getSize(); i++)
			delete waiting[i];
		for (size_t i = 0; i < executed.getSize(); i++)
		{
			delete executed[i];
		}
	}
};

class Factory
{
public:
	static VectorCommand* createCommand(IntVector& v, size_t type)
	{
		if (type == 0)
			return new SortCommand(v);
		else if(type == 1)
		{
			size_t from;
			size_t to;
			std::cin >> from >> to;

			return new SwapCommand(v, from, to);
		}
		throw std::invalid_argument("Invalid type");
	}
};

int main()
{
	IntVector v;
	for (int i = 9; i >= 0; i--) {
		v.pushBack(i);
	}

	CommandExecutor ce;

	VectorCommand* vc1 = new SwapCommand(v, 4, 5);
	VectorCommand* vc2 = new SortCommand(v);

	ce.addCommand(vc1);
	ce.addCommand(vc2);
	printArray(v);
	ce.execute();
	printArray(v);
	ce.execute();
	printArray(v);
	ce.undo();
	printArray(v);
	ce.undo();
	printArray(v);
}