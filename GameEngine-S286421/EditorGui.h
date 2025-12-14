#pragma once
#include <vector>
#include <memory>
#include <IGuiWindow.h>

class EditorGui : public IGuiWindow
{
public:
	static EditorGui* _instance;
	static EditorGui& const INSTANCE();
	void DrawWindow() override;
};