#pragma once
#include "Document.h"

class Viewer
{
protected:
	String name;
public:
	void view(const Document& document);
};

