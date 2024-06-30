#pragma once
#include "VectorCommand.h"

class SortCommand : public VectorCommand
{
private:
	IntVector* snapshot = nullptr;
public:
	SortCommand(IntVector& v);
	~SortCommand();

	void execute() override;
	void undo() override;
};

