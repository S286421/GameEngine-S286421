#include "EditorGui.h"

void EditorGui::DrawWindow()
{ }

void EditorGui::Receive(const IEventData * message, const std::string & topic)
{
}

EditorGui& const EditorGui::INSTANCE()
{
	if (!EditorGui::_instance)
		EditorGui::_instance = new EditorGui();

	return *EditorGui::_instance;
}
EditorGui* EditorGui::_instance = nullptr;

EditorGui::EditorGui()
{
	Broker::INSTANCE().Subscribe("MouseButtonUpdate", this);
}