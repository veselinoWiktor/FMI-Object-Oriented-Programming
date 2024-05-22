#include "Commenter.h"

void Commenter::comment(Document& document, const Comment& comment)
{
	document.addComment(comment);
}

void Commenter::comment(Document& document, Comment&& comment)
{
	document.addComment(std::move(comment));
}
