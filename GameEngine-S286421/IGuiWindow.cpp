#include "IGuiWindow.h"

void IGuiWindow::DrawWindows()
{
	for (auto& window : Windows)
	{
		window->DrawWindow();
		window->DrawWindows();
	}
}

void IGuiWindow::AttachChildWindow(IGuiWindow* Window)
{
	Windows.push_back(Window);
}

IGuiWindow* IGuiWindow::GetChildWindow(uint16_t Index)
{
	if (Index >= Windows.size())
		throw std::exception::exception("Index out of range");

	return Windows[Index];
}

IGuiWindow* IGuiWindow::RemoveChildWindow(uint16_t Index)
{
	if (Index >= Windows.size())
		throw std::exception::exception("Index out of range");

	IGuiWindow* temp = Windows[Index];
	Windows.erase(Windows.begin() + Index);
	return temp;
}

void IGuiWindow::RemoveChildWindow(IGuiWindow* window)
{
	Windows.erase(std::remove_if(Windows.begin(), Windows.end(), [&](const IGuiWindow* ptr) {return ptr && ptr == window;}), Windows.end());
}