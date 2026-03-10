#include "IDirectoryItem.h"
#include "ResourceManager.h"
#include "ImGui/imgui.h"

/// <summary>
/// Initialises IDirectoryItem; sets the IDirectoryItem class' IconTexture and Entry variables to the given iconTexture and entry
/// </summary>
/// <param name="iconTexture"></param>
/// <param name="entry"></param>
IDirectoryItem::IDirectoryItem(std::shared_ptr<SDL_Texture> iconTexture, std::filesystem::directory_entry entry)
{
	IconTexture = iconTexture;
	Entry = entry;
}

/// <summary>
/// Return the std::shared_ptr<SDL_Texture> IconTexture
/// </summary>
/// <returns></returns>
std::shared_ptr<SDL_Texture> IDirectoryItem::GetTextureRef()
{
	return IconTexture;
}

/// <summary>
/// Returns the std::filesystem::directory_entry& Entry
/// </summary>
/// <returns></returns>
const std::filesystem::directory_entry& IDirectoryItem::GetDirectoryEntry() const
{
	return Entry;
}

/// <summary>
/// Draws the icons of files in the asset window; used by AssetWindow in AssetWindow::DrawWindow()
/// </summary>
/// <returns></returns>
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
