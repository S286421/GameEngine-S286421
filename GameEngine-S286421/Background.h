#pragma once
#include "SDL3/SDL.h"
#include <string>
#include <memory>

class Background
{
public:
	SDL_Texture* LoadBackground(std::shared_ptr<SDL_Renderer>, const char *);
	void RenderBackground(std::shared_ptr<SDL_Renderer>, SDL_Texture*);
};

