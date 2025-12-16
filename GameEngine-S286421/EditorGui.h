#pragma once
#include <vector>
#include <memory>
#include "IGuiWindow.h"
#include "IDirectoryItem.h"
#include "Subscriber.h"

class EditorGui : public IGuiWindow, public Subscriber
{
public:
	EditorGui();
	static EditorGui* _instance;
	static EditorGui& const INSTANCE();
	void DrawWindow() override;
	IDirectoryItem* AssetMouseDrag = nullptr;

	// Inherited via Subscriber
	void Receive(const IEventData* message, const std::string& topic) override;
};