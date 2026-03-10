#include "IGuiWindow.h"

/// <summary>
/// Calls IGuiWindow::DrawWindow() for every IGuiWindow in the Windows vector, and calls itself to check for child windows attached to the items in the vector
/// </summary>
void IGuiWindow::DrawWindows()
{
	for (auto& window : Windows)
	{
		window->DrawWindow();
		window->DrawWindows();
	}
}

/// <summary>
/// Adds the given Window to the Windows vector
/// </summary>
/// <param name="Window"></param>
void IGuiWindow::AttachChildWindow(IGuiWindow* Window)
{
	Windows.push_back(Window);
}

/// <summary>
/// Searches for a child window in the Windows vector at the given Index, and returns it if found
/// </summary>
/// <param name="Index"></param>
/// <returns></returns>
IGuiWindow* IGuiWindow::GetChildWindow(uint16_t Index)
{
	if (Index >= Windows.size())
		throw std::exception::exception("Index out of range");

	return Windows[Index];
}

/// <summary>
/// Removes the child window in the Windows vector at the given Index, and returns a copy of the child window
/// </summary>
/// <param name="Index"></param>
/// <returns></returns>
IGuiWindow* IGuiWindow::RemoveChildWindow(uint16_t Index)
{
	if (Index >= Windows.size())
		throw std::exception::exception("Index out of range");

	IGuiWindow* temp = Windows[Index];
	Windows.erase(Windows.begin() + Index);
	return temp;
}

/// <summary>
/// Removes the given window from the Windows vector
/// </summary>
/// <param name="window"></param>
void IGuiWindow::RemoveChildWindow(IGuiWindow* window)
{
	Windows.erase(std::remove_if(Windows.begin(), Windows.end(), [&](const IGuiWindow* ptr) {return ptr && ptr == window;}), Windows.end());
}