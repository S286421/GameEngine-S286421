#include "IDirectoryItem.h"
#include "ResourceManager.h"
#include "ImGui/imgui.h"

IDirectoryItem::IDirectoryItem(std::shared_ptr<SDL_Texture> iconTexture, std::filesystem::directory_entry entry)
{
	IconTexture = iconTexture;
	Entry = entry;
}

std::shared_ptr<SDL_Texture> IDirectoryItem::GetTextureRef()
{
	return IconTexture;
}

const std::filesystem::directory_entry& IDirectoryItem::GetDirectoryEntry() const
{
	return Entry;
}

bool IDirectoryItem::DrawIconButton()
{
	bool isClicked = false;

	ImGui::BeginChild(Entry.path().filename().string().c_str(), { 200,200 }, false);
	isClicked = ImGui::ImageButton("button", (ImTextureID)IconTexture.get(), { 100,100 });

	ImGui::Text(Entry.path().filename().string().c_str());
	ImGui::EndChild();
	EditorGui::INSTANCE().AssetMouseDrag = this;

	return isClicked;
}

void IDirectoryItem::OnClick()
{
}
