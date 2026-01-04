#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "IGuiWindow.h"
#include "Subscriber.h"
#include "MouseEventData.h"
#include "Hierarchy.h"

class IDirectoryItem;

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