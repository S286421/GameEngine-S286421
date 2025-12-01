#pragma once

#include "SDL3/SDL.h"
#include <memory>
#include <string>
#include "ResourceManager.h"
#include "ECS.h"
#include "Components.hpp"

class RendererSystem
{
public:
	static BitmapECS AddBitmapComponentToEntity(uint32_t EntityID, ECS& const ecs, std::string FileLocation, std::shared_ptr<SDL_Renderer> renderer, bool isTransparent = true);

	static void Render(ECS& const ecs, std::shared_ptr<SDL_Renderer> renderer);
};

