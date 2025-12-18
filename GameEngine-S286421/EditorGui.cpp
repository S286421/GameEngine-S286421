#include "EditorGui.h"

void EditorGui::DrawWindow()
{ }

void EditorGui::Receive(const IEventData * message, const std::string & topic)
{
	const MouseEventData* mouseEventData = static_cast<const MouseEventData*>(message);

	if (mouseEventData->mouseButton.button == SDL_BUTTON_LEFT && mouseEventData->mouseButton.type == SDL_EVENT_MOUSE_BUTTON_UP && AssetMouseDrag != nullptr)
	{
		SDL_Point mousePosition = { mouseEventData->mousePosition.x, mouseEventData->mousePosition.y };
		std::cout << "Mouse Button Update at position: (" << mousePosition.x << ", " << mousePosition.y << ")\n";

		Hierarchy::INSTANCE().AddGameObject(AssetMouseDrag->GetDirectoryEntry().path().string(), mousePosition.x, mousePosition.y, true);

		AssetMouseDrag = nullptr;
	}
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