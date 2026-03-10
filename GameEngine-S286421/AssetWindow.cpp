#include "AssetWindow.h"

/// <summary>
/// Initialises the AssetWindow; assigns pRenderer as a private renderer, adds the path to the assets folder to the dirStack, and calls AssetWindow::GetItemsInDirectory()
/// </summary>
/// <param name="pRenderer"></param>
AssetWindow::AssetWindow(const std::shared_ptr<SDL_Renderer>& pRenderer)
{
	p_renderer = pRenderer;
	std::string path = "./../Assets";
	std::filesystem::path dirPath(path);
	dirStack.push(dirPath);

	BackButtonTexture = ResourceManager::INSTANCE().LoadTexture("./../Assets/back button.png", true, pRenderer);

	GetItemsInDirectory();
}

/// <summary>
/// Deconstructs the AssetWindow; deletes all content in the window
/// </summary>
AssetWindow::~AssetWindow()
{
	for (int i = 0; i < content.size(); i++)
	{
		delete content[i];
	}
}

/// <summary>
/// Gets all assets using AssetWindow::GetItemsInDirectory(), then draws an asset window with all assets included
/// </summary>
void AssetWindow::DrawWindow()
{
	ImGui::Begin("Assets");

	if (ImGui::ImageButton("button", (ImTextureID)BackButtonTexture.get(), { 64, 64 }))
	{
		if (dirStack.size() > 1)
		{
			dirStack.pop();
			GetItemsInDirectory();
		}
	}

	ImGui::BeginChild("Content Window", ImVec2(), true);

	for (int i = 0; i < content.size(); i++)
	{
		ImGui::SameLine();
		ImGui::PushID(i);
		
		if (content[i]->DrawIconButton())
		{
			if (content[i]->GetDirectoryEntry().is_directory())
			{
				dirStack.push(content[i]->GetDirectoryEntry().path());
				GetItemsInDirectory();
			}
			else
			{
				content[i]->OnClick();
			}
		}

		ImGui::PopID();
		ImGui::SameLine();
	}

	ImGui::EndChild();
	ImGui::End();
}

/// <summary>
/// Searches the assets folder, and checks if each item is an image file, a folder, or another file type
/// </summary>
void AssetWindow::GetItemsInDirectory()
{
	content.clear();
	std::filesystem::path dirPath = dirStack.top();
	Bitmap* bitmap = nullptr;
	for (const auto& entry : std::filesystem::directory_iterator(dirPath))
	{
		if (entry.path().extension() == ".bmp" || entry.path().extension() == ".jpg" || entry.path().extension() == ".png")
		{
			IDirectoryItem* File = new IDirectoryItem(ResourceManager::INSTANCE().LoadTexture(entry.path().string(), true, p_renderer), entry);
			content.push_back(File);
		}
		else if (entry.is_directory())
		{
			IDirectoryItem* Dir = new IDirectoryItem(ResourceManager::INSTANCE().LoadTexture("./../Assets/folder.png", true, p_renderer), entry);
			content.push_back(Dir);
			std::cout << "dir " << entry << std::endl;
		}
		else
		{
			IDirectoryItem* File = new IDirectoryItem(ResourceManager::INSTANCE().LoadTexture("./../Assets/kaboom.png", true, p_renderer), entry);
			content.push_back(File);
		}
		std::cout << entry.path() << std::endl;
	}
}