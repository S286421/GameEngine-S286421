#include "ResourceManager.h"

/// <summary>
/// Loads an image from a given FilePath, and converts it to a texture map (creating a transparent background if isTransparent is true)
/// </summary>
/// <param name="FilePath"></param>
/// <param name="isTransparent"></param>
/// <param name="renderer"></param>
/// <returns></returns>
std::shared_ptr<SDL_Texture> ResourceManager::LoadTexture(std::string FilePath, bool isTransparent, std::shared_ptr<SDL_Renderer> renderer)
{
	std::shared_ptr<SDL_Texture> texture;

	auto searchResult = TextureMap.find(FilePath);
	if (searchResult != TextureMap.end()) texture = TextureMap[FilePath];
	else
	{
		SDL_Surface* loadedSurface = IMG_Load(FilePath.c_str());

		if (loadedSurface == nullptr)
			SDL_Log("Unable to load image %s! SDL_image error: %s\n", FilePath.c_str(), SDL_GetError());
		else
		{
			if (isTransparent)
			{
				Uint32 colourKey = SDL_MapSurfaceRGBA(loadedSurface, 255, 0, 255, 0);
				SDL_SetSurfaceColorKey(loadedSurface, true, colourKey);
			}

			SDL_Texture* tempTex = SDL_CreateTextureFromSurface(renderer.get(), loadedSurface);
			texture = std::shared_ptr<SDL_Texture>(tempTex);

			if (tempTex == nullptr)
				SDL_Log("Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError());

			TextureMap[FilePath] = texture;

			SDL_DestroySurface(loadedSurface);
		}
	}

	return texture;
}

/// <summary>
/// Creates a resource manager instance and returns it; used to call the resource manager in other files
/// </summary>
/// <returns></returns>
ResourceManager& const ResourceManager::INSTANCE()
{
	if (!ResourceManager::_instance) ResourceManager::_instance = new ResourceManager();

	return *ResourceManager::_instance;
}
ResourceManager* ResourceManager::_instance = nullptr;
