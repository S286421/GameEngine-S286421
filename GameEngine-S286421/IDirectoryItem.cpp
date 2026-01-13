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

	if (ImGui::BeginDragDropSource())
	{
		ImGui::Image((ImTextureID)this->GetTextureRef().get(), { 100,100 });
		EditorGui::INSTANCE().AssetMouseDrag = this;
		ImGui::EndDragDropSource();
	}

	ImGui::Text(Entry.path().filename().string().c_str());
	ImGui::EndChild();

	return isClicked;
}

void IDirectoryItem::OnClick()
{
}
