#pragma once

#include "json.hpp"

#include <memory>
struct SDL_Renderer;

class ISaveLoadable
{
public:
	virtual ~ISaveLoadable() = default;
	virtual nlohmann::json Save() const = 0;
	virtual void Load(nlohmann::json LoadData, std::shared_ptr<SDL_Renderer> renderer) = 0;
};

