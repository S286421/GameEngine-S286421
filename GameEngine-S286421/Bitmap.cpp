#include "Bitmap.h"

Bitmap::Bitmap(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y,bool isTransparent)
{
	_renderer = renderer;
	_xPosition = x;
	_yPosition = y;

	float w, h;
	_texture = ResourceManager::INSTANCE().LoadTexture(path, isTransparent, _renderer);
	SDL_GetTextureSize(_texture.get(), &w, &h);
	_width = w;
	_height = h;
}

void Bitmap::Draw()
{
	Draw(_xPosition, _yPosition);
}

void Bitmap::Draw(int x, int y)
{
	SDL_FRect dstRect = { x, y, _width, _height };
	SDL_RenderTexture(_renderer.get(), _texture.get(), NULL, &dstRect);
}