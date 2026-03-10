#include "EditorGui.h"
#include "IDirectoryItem.h"

void EditorGui::DrawWindow()
{ }

/// <summary>
/// Handles clicking and drag and drop functionality using MouseEventData
/// </summary>
/// <param name="message"></param>
/// <param name="topic"></param>
void EditorGui::Receive(const IEventData * message, const std::string & topic)
{
	const MouseEventData* mouseEventData = static_cast<const MouseEventData*>(message);

	if (mouseEventData->mouseButton.button == SDL_BUTTON_LEFT && mouseEventData->mouseButton.type == SDL_EVENT_MOUSE_BUTTON_UP && AssetMouseDrag != nullptr)
	{
		SDL_Point mousePosition = { mouseEventData->mousePosition.x, mouseEventData->mousePosition.y };
		std::cout << "Mouse Button Update at position: (" << mousePosition.x << ", " << mousePosition.y << ")\n";

		Hierarchy::INSTANCE().AddGameObject(AssetMouseDrag->GetDirectoryEntry().path().string().c_str(), mousePosition.x, mousePosition.y, true);

		AssetMouseDrag = nullptr;
	}
}

/// <summary>
/// Creates an EditorGui instance and returns it; used to call the EditorGui in other files
/// </summary>
/// <returns></returns>
EditorGui& const EditorGui::INSTANCE()
{
	if (!EditorGui::_instance)
		EditorGui::_instance = new EditorGui();

	return *EditorGui::_instance;
}
EditorGui* EditorGui::_instance = nullptr;

/// <summary>
/// Initialises the EditorGui; subscribes to the "MouseButtonUpdate" message
/// </summary>
EditorGui::EditorGui()
{
	Broker::INSTANCE().Subscribe("MouseButtonUpdate", this);
}