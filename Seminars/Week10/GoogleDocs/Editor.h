#pragma once
#include "Commenter.h"

class Editor : public Commenter
{
public:
	void edit(Document& document, const String& content);
	void edit(Document& document, String&& content);	
};

