#pragma once
#include <vector>
#include <memory>

class IGuiWindow
{
private:
	std::vector<IGuiWindow*> Windows;
public:
	void DrawWindows();
	virtual void DrawWindow() = 0;
	void AttachChildWindow(IGuiWindow* Window);
	IGuiWindow* GetChildWindow(uint16_t Index);
	IGuiWindow* RemoveChildWindow(uint16_t Index);
	void RemoveChildWindow(IGuiWindow* window);
};