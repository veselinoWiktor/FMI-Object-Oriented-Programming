#pragma once
#include "Viewer.h"

class Commenter : public Viewer
{
public:
	void comment(Document& document, const Comment& comment);
	void comment(Document& document, Comment&& comment);
};

