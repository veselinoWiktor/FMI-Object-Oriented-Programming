#include "Document.h"

const String& Document::getContent() const
{
	return content;
}

void Document::addComment(const Comment& comment)
{
	if (currentCommentsCount >= 50)
	{
		return;
	}

	comments[currentCommentsCount++] = comment;
}

void Document::addComment(Comment&& comment)
{
	if (currentCommentsCount >= 50)
	{
		return;
	}

	comments[currentCommentsCount++] = std::move(comment);
}

void Document::setContent(const String& text)
{
	content = text;
}

void Document::setContent(String&& text)
{
	content = std::move(text);
}
