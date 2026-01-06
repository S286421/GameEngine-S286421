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
	this->path = path;
}

void Bitmap::Draw()
{
	Draw(_xPosition, _yPosition);
}

void Bitmap::Draw(int x, int y)
{
	_xPosition = x;
	_yPosition = y;

	SDL_FRect dstRect = { x, y, _width, _height };
	SDL_RenderTexture(_renderer.get(), _texture.get(), NULL, &dstRect);
}

SDL_Rect Bitmap::GetImageBounds() const
{
	SDL_Rect a = { _xPosition, _yPosition, _width, _height };
	return a;
}

std::shared_ptr<SDL_Renderer> Bitmap::GetRenderer()
{
	return _renderer;
}

std::shared_ptr<SDL_Texture> Bitmap::GetTextureRef()
{
	return _texture;
}