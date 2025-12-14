#include "EditorGui.h"

void EditorGui::DrawWindow()
{ }

EditorGui& const EditorGui::INSTANCE()
{
	if (!EditorGui::_instance)
		EditorGui::_instance = new EditorGui();

	return *EditorGui::_instance;
}
EditorGui* EditorGui::_instance = nullptr;