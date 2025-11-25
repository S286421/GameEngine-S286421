#pragma once

#include <map>
#include <string>
#include <memory>
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "SDL_Deleter.h"

class ResourceManager
{
public:
	std::shared_ptr<SDL_Texture> LoadTexture(std::string, bool, std::shared_ptr<SDL_Renderer>);
	static ResourceManager* _instance;
	static ResourceManager& const INSTANCE();
private:
	std::map<std::string, std::shared_ptr<SDL_Texture>> TextureMap;
};

