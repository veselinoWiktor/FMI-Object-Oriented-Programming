#include "SortCommand.h"

SortCommand::SortCommand(IntVector& v) : VectorCommand(v)
{
}

SortCommand::~SortCommand()
{
	delete snapshot;
}

void SortCommand::execute()
{
	if (snapshot)
	{
		delete snapshot;
	}

	snapshot = new IntVector(v);

	for (size_t i = 0; i < v.getSize() - 1; i++)
	{
		size_t targetIdx = i;
		for (size_t j = i + 1; j < v.getSize(); j++)
		{
			if (v[j] < v[targetIdx])
				targetIdx = j;
		}

		if (targetIdx != i)
			std::swap(v[targetIdx], v[i]);
	}
}

void SortCommand::undo()
{
	if (snapshot)
	{
		v = std::move(*snapshot);
		delete snapshot;
		snapshot = nullptr;
	}
}
