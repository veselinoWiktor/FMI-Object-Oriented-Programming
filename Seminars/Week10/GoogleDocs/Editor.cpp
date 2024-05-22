#include "Editor.h"

void Editor::edit(Document& document, const String& content)
{
	document.setContent(content);
}

void Editor::edit(Document& document, String&& content)
{
	document.setContent(std::move(content));
}
