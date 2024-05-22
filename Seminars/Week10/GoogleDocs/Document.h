#pragma once
#include "String.h"

struct Comment
{
	String text;
	String createdBy;
};

class Document
{
private:
	String content;
	Comment comments[50];
	unsigned currentCommentsCount = 0;
public:
	const String& getContent() const;

	void addComment(const Comment& comment);
	void addComment(Comment&& comment);

	void setContent(const String& text);
	void setContent(String&& text);
};

