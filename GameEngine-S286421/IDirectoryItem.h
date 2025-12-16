#pragma once
#include <string>
#include <memory>
#include <filesystem>
#include "EditorGui.h"

struct SDL_Texture;

class IDirectoryItem
{
protected:
	std::shared_ptr<SDL_Texture> IconTexture;
	std::filesystem::directory_entry Entry;
public:
	IDirectoryItem(std::shared_ptr<SDL_Texture> iconTexture, std::filesystem::directory_entry entry);
	~IDirectoryItem() = default;
	void OnClick();
	bool DrawIconButton();

	std::shared_ptr<SDL_Texture> GetTextureRef();

	const std::filesystem::directory_entry& GetDirectoryEntry() const;
};

