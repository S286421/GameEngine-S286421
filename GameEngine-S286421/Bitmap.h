#pragma once

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "SDL_Deleter.h"
#include "ResourceManager.h"
#include <memory>
#include <string>

class Bitmap
{
public:
	Bitmap(
		std::shared_ptr<SDL_Renderer> renderer,
		const std::string path, int x, int y, bool isTransparent);
	void Draw();
	void Draw(int x, int y);
	SDL_Rect GetImageBounds() const;
	std::shared_ptr<SDL_Renderer> GetRenderer();
	std::shared_ptr<SDL_Texture> GetTextureRef();
private:
	std::shared_ptr<SDL_Renderer> _renderer;
	int _xPosition;
	int _yPosition;
	int _width;
	int _height;

	std::shared_ptr<SDL_Texture> _texture;
};

