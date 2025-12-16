#pragma once
#include "IGuiWindow.h"
#include "Bitmap.h"
#include "ImGui/imgui.h"
#include "IDirectoryItem.h"
#include <string>
#include <filesystem>
#include <iostream>
#include <stack>

struct SDL_Renderer;
class Bitmap;

class AssetWindow : public IGuiWindow
{
public:
	AssetWindow(const std::shared_ptr<SDL_Renderer>& pRenderer);
	~AssetWindow();
	void DrawWindow() override;
	std::stack<std::filesystem::path> dirStack;
	void GetItemsInDirectory();
	std::shared_ptr<SDL_Texture> BackButtonTexture;

private:
	std::vector<IDirectoryItem*> content;
	std::shared_ptr<SDL_Renderer> p_renderer;
};

